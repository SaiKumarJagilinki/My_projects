CC=gcc
target=main.o stu_add.o stu_show.o stu_save.o stu_del.o stu_read.o stu_exit.o stu_sort.o stu_del_all.o stu_rev.o stu_mod.o
student: ${target}
	${CC} ${target} -o student
main.o:main.c
	${CC} -c main.c
stu_add.o:stu_add.c
	${CC} -c stu_add.c
stu_show.o:stu_show.c
	${CC} -c stu_show.c
stu_save.o:stu_save.c
	${CC} -c stu_save.c
stu_del.o:stu_del.c
	${CC} -c stu_del.c
stu_read.o:stu_read.c
	${CC} -c stu_read.c
stu_exit.o:stu_exit.c
	${CC} -c stu_exit.c
stu_sort.o:stu_sort.c
	${CC} -c stu_sort.c
stu_del_all.o:stu_del_all.c
	${CC} -c stu_del_all.c
stu_rev.o:stu_rev.c
	${CC} -c stu_rev.c
stu_mod.o:stu_mod.c
	${CC} -c stu_mod.c
clear:
	@echo "cleaned"
	@rm -vr *.o 
