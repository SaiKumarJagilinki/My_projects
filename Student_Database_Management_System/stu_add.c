#include"header.h"
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

