#include"header.h"
void stu_mod(stu**ptr)
{
if(*ptr==0)
{
printf("no records to modify\n");
return;
}
int c=0;
while(1)
{
if(c==1)
break;
char op;
printf("\033[31mr/R.modify rno\nn/N.modify name\np/P.modify percentage\n\033[0m");
printf("Enter ur choice:");
scanf(" %c",&op);
switch(op)
{
case 'r':case 'R':mod_rno(ptr);c++;break;
case 'n':case 'N':mod_name(ptr);c++;break;
case 'p':case 'P':mod_pct(ptr);c++;break;
default:printf("select 'r' 'R' 'n' 'N' 'p' 'P'\n");
}
}
}
void mod_rno(stu**ptr)
{
int srno;
printf("Enter rno to search:");
scanf("%d",&srno);
stu *t=*ptr;
while(t)
{
if(t->rno==srno)
{
del_byrno(ptr);
stu_add(ptr);
printf("rno modified successfully\n");
return;
}
t=t->next;
}
printf("rno not found\n");
}
void mod_name(stu**ptr)
{
char str[40],mstr[40];
printf("Enter name to search:");
scanf("%s",str);
stu *t=*ptr,*tp;
int sc=0;
while(t)
{
if(strcmp(t->name,str)==0)
{
tp=t;
sc++;
}
t=t->next;
}
if(sc==1)
{
printf("enter modified name:");
scanf("%s",mstr);
strcpy(tp->name,mstr);
printf("name modified successfully\n");
return;
}
else if(sc>1)
{
t=*ptr;
while(t)
{
if(strcmp(t->name,str)==0)
printf("%d %s %f\n",t->rno,t->name,t->pct);
t=t->next;
}
mod_rno(ptr);
}
else
printf("name not found\n");
}
void mod_pct(stu**ptr)
{
float spct,mpct;
int sc=0;
printf("Enter percent to search:");
scanf("%f",&spct);
stu *t=*ptr,*tp;
while(t)
{
if(t->pct==spct)
{
tp=t;
sc++;
}
t=t->next;
}
if(sc==1)
{
printf("Enter modified pecenatge:");
scanf("%f",&mpct);
tp->pct=mpct;
printf("percentage modified successfully\n");
return;
}
else if(sc>1)
{
t=*ptr;
while(t)
{
if(t->pct==spct)
printf("%5d%16s\t\t%.1f\n",t->rno,t->name,t->pct);
t=t->next;
}
mod_rno(ptr);
}
else
printf("percentage not found\n");
}




