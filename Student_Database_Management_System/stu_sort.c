#include"header.h"
void sort_name(stu*,int);
void sort_pct(stu*,int);
void stu_sort(stu*ptr)
{
if(ptr==0)
{
printf("no records to sort\n");
return;
}
int c,c1=0;
stu *t=ptr;
for(c=0;t;t=t->next,c++);
while(1)
{
if(c1==1)
break;
char op;
printf("\033[31mn/N.sort with name\np/P.sort with percentage\n\033[0m");
printf("Enter your choice:");
scanf(" %c",&op);
switch(op)
{
case 'n':case 'N':sort_name(ptr,c);c1++;break;
case 'p':case 'P':sort_pct(ptr,c);c1++;break;
default:printf("select 'n' 'N' 'p' 'P'\n");
}
}
}
void sort_name(stu*ptr,int c)
{
stu *p1,*p2,t;
int i,j;
p1=ptr;
for(i=0;i<c-1;i++)
{
p2=p1->next;
for(j=i+1;j<c;j++)
{
if(strcmp(p1->name,p2->name)>0)
{
t.rno=p1->rno;
strcpy(t.name,p1->name);
t.pct=p1->pct;

p1->rno=p2->rno;
strcpy(p1->name,p2->name);
p1->pct=p2->pct;

p2->rno=t.rno;
strcpy(p2->name,t.name);
p2->pct=t.pct;
}
p2=p2->next;
}
p1=p1->next;
}
printf("sorted by name successfully\n");
}
void sort_pct(stu*ptr,int c)
{
stu *p1,*p2,t;
int i,j;
p1=ptr;
for(i=0;i<c-1;i++)
{
p2=p1->next;
for(j=i+1;j<c;j++)
{
if(p1->pct>p2->pct)
{
t.rno=p1->rno;
strcpy(t.name,p1->name);
t.pct=p1->pct;

p1->rno=p2->rno;
strcpy(p1->name,p2->name);
p1->pct=p2->pct;

p2->rno=t.rno;
strcpy(p2->name,t.name);
p2->pct=t.pct;
}
p2=p2->next;
}
p1=p1->next;
}
printf("sorted by  pct successfully\n");
}
