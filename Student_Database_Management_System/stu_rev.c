#include"header.h"
void stu_rev(stu**ptr)
{
if(*ptr==0)
{
printf("no records to reverse\n");
return;
}
stu *t=*ptr;
int c=0,i;
for(;t;t=t->next,c++);
stu **a=malloc(sizeof(stu)*c);
t=*ptr;
for(i=0;i<c;i++)
{
a[i]=t;
t=t->next;
}
for(i=i-1;i>=1;i--)
a[i]->next=a[i-1];
a[0]->next=0;
*ptr=a[c-1];
printf("records reversed successfully\n");
}
