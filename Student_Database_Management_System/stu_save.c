#include"header.h"
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
