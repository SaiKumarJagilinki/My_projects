#include"header.h"
void stu_del(stu**ptr)
{
if(*ptr==0)
{
printf("no records to delete\n");
return;
}
int c=0;
while(1)
{
if(c==1)
break;
char op;
printf("\033[31mr/R.based on rno to delete\nn/N.based on name to delete\n\033[0m");
printf("enter ur choice:");
scanf(" %c",&op);
switch(op)
{
case 'r':case 'R':del_byrno(ptr);c++;break;
case 'n':case 'N':del_byname(ptr);c++;break;
default:printf("select 'r' or 'n'\n");
}
}
}
void del_byrno(stu**ptr)
{
        stu *del,*prev;
	int rno;
	printf("enter rno to delete:");
	scanf("%d",&rno);
	del=*ptr;
	while(del)
	{
	if(rno==del->rno)
	{
	if(del==*ptr)
	*ptr=del->next;
	else
	prev->next=del->next;
	free(del);
	del=0;
	printf("the record with %d rno deleted\n",rno);
	return;
	}
	prev=del;
	del=del->next;
	}
	printf("rno not found\n");
}
void del_byname(stu**ptr)
{
	char str[40];
	int dc=0;
	stu *del,*prev;
	printf("enter name to delete:");
	scanf("%s",str);
	del=*ptr;
	while(del)
	{
	if(strcmp(del->name,str)==0)
	dc++;
	del=del->next;
	}
	if(dc==1)
	{
	del=*ptr;
		while(del)
		{
			if(strcmp(del->name,str)==0)
			{
				if(del==*ptr)
				*ptr=del->next;
				else
				{
				del=prev->next;
				prev->next=del->next;
				}
			free(del);
			del=0;
			printf("the record with %s name deleted\n",str);
			return;
			}
		prev=del;
		del=del->next;
		}
	}
	else if(dc>1)
	{
		prev=*ptr;
		printf("the records with same name\n");
		while(prev)
		{
		if(strcmp(prev->name,str)==0)
		printf("%d\t%s\t%.1f\n",prev->rno,prev->name,prev->pct);
		prev=prev->next;
		}
		del_byrno(ptr);
	}
	else
	printf("the record with %s name not found\n",str);
}
