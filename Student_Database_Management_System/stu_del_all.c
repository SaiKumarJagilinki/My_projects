#include"header.h"
void stu_del_all(stu**ptr)
{
if(*ptr==0)
{
printf("no records to delete\n");
return;
}
stu *del=*ptr;
while(del)
{
*ptr=del->next;
free(del);
del=0;
del=*ptr;
}
printf("all records deleted successfully\n");
}
