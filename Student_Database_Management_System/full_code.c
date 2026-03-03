#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
typedef struct st
{
int rno;
char name[30];
float pct;
struct st *next;
}stu;
void stu_add(stu**);
void stu_show(stu*);
void stu_save(stu*);
void stu_del(stu**);
void del_byrno(stu**);
void del_byname(stu**);
void stu_read(stu**);
void stu_exit(stu*);
void stu_sort(stu*);
void stu_del_all(stu**);
void stu_rev(stu**);
void stu_mod(stu**);
void mod_rno(stu**);
void mod_name(stu**);
void mod_pct(stu**);
void main()
{
stu *hptr=0;
char op;
while(1)
{
printf("\033[033m                                  *********STUDENT RECORD MENU*********\n");
printf("a/A.add record\td/D.delete record\ts/S.show records\tm/M.modify record\tv/V.save rcord\ne/E.exit\tt/T.sort the rocords\tl/L.delete all records\tr/R.reverse the records\tf/F.read records\n");
printf("Enter your choice:");
scanf(" %c",&op);
printf("\033[0m");
system("clear");
switch(op)
{
case 'a':case 'A':stu_add(&hptr);break;
case 'd':case 'D':stu_del(&hptr);break;
case 's':case 'S':stu_show(hptr);break;
case 'm':case 'M':stu_mod(&hptr);break;
case 'v':case 'V':stu_save(hptr);break;
case 'e':case 'E':stu_exit(hptr);break;
case 't':case 'T':stu_sort(hptr);break;
case 'l':case 'L':stu_del_all(&hptr);break;
case 'r':case 'R':stu_rev(&hptr);;break;
case 'f':case 'F':stu_read(&hptr);break;
default :printf("invalid choice\n");
}
}
}
void stu_add(stu**ptr)
{
stu *new=calloc(1,sizeof(stu));
printf("enter details:\n");
scanf("%d%s %f",&new->rno,new->name,&new->pct);
if(*ptr==0 || (new->rno)<(*ptr)->rno )
{
new->next=*ptr;
*ptr=new;
}
else
{
stu *pos=*ptr;
while(pos->next!=0 && (new->rno)>pos->next->rno )
pos=pos->next;
if( (pos->next!=0 &&   pos->next->rno==new->rno)||(pos->rno==new->rno))
{
printf("duplicate rno\n");
return;
}
new->next=pos->next;
pos->next=new;
}
}

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




void stu_save(stu*ptr)
{
if(ptr==0)
{
printf("no records to save\n");
return;
}
FILE *fp=fopen("std.txt","w");
while(ptr)
{
fprintf(fp,"%d %s %f\n",ptr->rno,ptr->name,ptr->pct);
ptr=ptr->next;
}
printf("file saved successfully\n");
fclose(fp);
}
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
