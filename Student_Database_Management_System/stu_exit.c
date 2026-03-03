#include"header.h"
void stu_exit(stu*ptr)
{
int c=0;
while(1)
{
if(c==1)
break;
char op;
printf("\033[31ms/S.save&exit\ne/E.exit without save\n\033[0m");
printf("Enter your choice:");
scanf(" %c",&op);
switch(op)
{
case 's':case 'S':stu_save(ptr);c++;break;
case 'e':case 'E':exit(0);
default:printf("select 'e' 'E' 's' 'S'\n");
}
}
}
