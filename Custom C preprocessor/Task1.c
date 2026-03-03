#include"header.h"
void remove_comments(char*src,char*task1)
{
FILE *sf=fopen(src,"r");
FILE *df=fopen(task1,"w");
if(sf==NULL)
{
printf("src file is not present\n");
return;
}
char ch1,ch2;
while((ch1=fgetc(sf))!=EOF)
{
if(ch1=='/')
{
   ch2=fgetc(sf);
    if(ch2=='/')
     {
     while( (ch1=fgetc(sf))!='\n' && ch1!=EOF );
     fputc('\n',df);
     }
    else if(ch2=='*')
    {
   ch1=fgetc(sf);
  ch2=fgetc(sf);
while(1)
{
if(ch1=='*'&&ch2=='/')
break;
ch1=ch2;
ch2=fgetc(sf);
}
/*   while( (ch2=fgetc(sf))!=EOF  )    
    {
   if(ch1=='*'&&ch2=='/')
    break;
    ch1=ch2;
    }*/
    }
}
else
fputc(ch1,df);
}
fclose(sf);
fclose(df);
}
