#include"header.h"
void stu_show(stu*ptr)
{
if(ptr==0)
{
printf("no records to show\n");
return;
}
printf("\033[31m%5s%16s\t\t%s\n\033[0m","RNO","NAME","PERCENT");
while(ptr)
{
printf("%5d%16s\t\t%.1f\n",ptr->rno,ptr->name,ptr->pct);
ptr=ptr->next;
}
}
