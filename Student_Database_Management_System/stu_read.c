#include"header.h"
void stu_read(stu**ptr)
{
FILE *fp=fopen("std.txt","r");
if(fp==0)
{
printf("no file\n");
return;
}
while(1)
{
stu *new=calloc(1,sizeof(stu));
if(fscanf(fp,"%d%s%f",&new->rno,new->name,&new->pct)==EOF)
break;
if(*ptr==0)
*ptr=new;
else
{
stu*last=*ptr;
while(last->next)
last=last->next;
last->next=new;
}
}
printf("file read successfully\n");
}
