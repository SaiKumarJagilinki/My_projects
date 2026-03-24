#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/ioctl.h>
#include <linux/poll.h>

#define DEVICE_NAME "vchardev"
#define CLASS_NAME  "vchar"
#define BUF_SIZE    1024

#define VCHAR_IOC_MAGIC  'V'
#define VCHAR_IOCTL_CLEAR_BUFFER _IO(VCHAR_IOC_MAGIC, 0)
#define VCHAR_IOCTL_GET_SIZE     _IOR(VCHAR_IOC_MAGIC, 1, int)

static dev_t dev_num;
static struct cdev vchar_cdev;
static struct class *vchar_class;
static struct device *vchar_device;

static DECLARE_KFIFO(vchar_fifo, char, BUF_SIZE);
static DEFINE_MUTEX(vchar_mutex);
static DECLARE_WAIT_QUEUE_HEAD(read_queue);

static int vchar_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[vchardev] Device opened\n");
    return 0;
}

static int vchar_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "[vchardev] Device closed\n");
    return 0;
}

static ssize_t vchar_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    if (file->f_flags & O_NONBLOCK && kfifo_is_empty(&vchar_fifo))
        return -EAGAIN;

    if (mutex_lock_interruptible(&vchar_mutex))
        return -ERESTARTSYS;

    while (kfifo_is_empty(&vchar_fifo)) {
        mutex_unlock(&vchar_mutex);
        if (file->f_flags & O_NONBLOCK)
            return -EAGAIN;
        if (wait_event_interruptible(read_queue, !kfifo_is_empty(&vchar_fifo)))
            return -ERESTARTSYS;
        if (mutex_lock_interruptible(&vchar_mutex))
            return -ERESTARTSYS;
    }

    ret = kfifo_to_user(&vchar_fifo, buf, count, &copied);
    mutex_unlock(&vchar_mutex);

    printk(KERN_INFO "[vchardev] Read %u bytes\n", copied);
    return ret ? ret : copied;
}

static ssize_t vchar_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    if (mutex_lock_interruptible(&vchar_mutex))
        return -ERESTARTSYS;

    ret = kfifo_from_user(&vchar_fifo, buf, count, &copied);
    mutex_unlock(&vchar_mutex);

    if (copied)
        wake_up_interruptible(&read_queue);

    printk(KERN_INFO "[vchardev] Wrote %u bytes\n", copied);
    return ret ? ret : copied;
}

static long vchar_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int size;
    switch (cmd) {
        case VCHAR_IOCTL_CLEAR_BUFFER:
            mutex_lock(&vchar_mutex);
            kfifo_reset(&vchar_fifo);
            mutex_unlock(&vchar_mutex);
            printk(KERN_INFO "[vchardev] Buffer cleared\n");
            break;
        case VCHAR_IOCTL_GET_SIZE:
            mutex_lock(&vchar_mutex);
            size = kfifo_len(&vchar_fifo);
            mutex_unlock(&vchar_mutex);
            if (copy_to_user((int __user *)arg, &size, sizeof(int)))
                return -EFAULT;
            printk(KERN_INFO "[vchardev] Buffer size: %d\n", size);
            break;
        default:
            return -ENOTTY;
    }
    return 0;
}

static __poll_t vchar_poll(struct file *file, poll_table *wait)
{
    __poll_t mask = 0;
    poll_wait(file, &read_queue, wait);
    if (!kfifo_is_empty(&vchar_fifo))
        mask |= POLLIN | POLLRDNORM;
    return mask;
}

static struct file_operations vchar_fops = {
    .owner          = THIS_MODULE,
    .open           = vchar_open,
    .release        = vchar_release,
    .read           = vchar_read,
    .write          = vchar_write,
    .unlocked_ioctl = vchar_ioctl,
    .poll           = vchar_poll,
};

static int __init vchar_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "[vchardev] Failed to alloc chrdev region\n");
        return ret;
    }

    cdev_init(&vchar_cdev, &vchar_fops);
    vchar_cdev.owner = THIS_MODULE;

    ret = cdev_add(&vchar_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "[vchardev] Failed to add cdev\n");
        return ret;
    }

    vchar_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(vchar_class)) {
        cdev_del(&vchar_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "[vchardev] Failed to create class\n");
        return PTR_ERR(vchar_class);
    }

    vchar_device = device_create(vchar_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(vchar_device)) {
        class_destroy(vchar_class);
        cdev_del(&vchar_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "[vchardev] Failed to create device\n");
        return PTR_ERR(vchar_device);
    }

    INIT_KFIFO(vchar_fifo);
    mutex_init(&vchar_mutex);

    printk(KERN_INFO "[vchardev] Module loaded: Major=%d Minor=%d\n", MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit vchar_exit(void)
{
    device_destroy(vchar_class, dev_num);
    class_destroy(vchar_class);
    cdev_del(&vchar_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "[vchardev] Module unloaded\n");
}

module_init(vchar_init);
module_exit(vchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Virtual Character Device Driver with Circular Buffer and IOCTL");
MODULE_VERSION("1.0");
