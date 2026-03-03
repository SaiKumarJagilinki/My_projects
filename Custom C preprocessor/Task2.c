#include"header.h"
void search_inc_header(char*task1,char*task2)
{
FILE *sf=fopen(task1,"r");
FILE *df=fopen(task2,"w");
fclose(df);
char hdr[100]="/usr/include/";
char ch;
int sl=0,ll=0;
while( (ch=fgetc(sf))!=EOF  )
{
sl++;
if(ch=='\n')
{
if(sl>ll)
ll=sl;
sl=0;
}
}
rewind(sf);
char *str,*q,*thdr;
str=calloc(ll+1,sizeof(char));
while(fgets(str,ll+1,sf))
{
thdr=malloc(sizeof(char)*100);
strcpy(thdr,hdr);
if(strstr(str,"main()"))
break;
if(strstr(str,"#include"))
{
strcat(thdr,str+9);
if( (q=strrchr(thdr,'>') )|| (q=strrchr(thdr,'"')) )
*q='\0';
include_header(thdr,task2);
free(thdr);
thdr=NULL;
}
}
free(str);
str=0;
}
void include_header(char*src,char*dest)
{
FILE*sf=fopen(src,"r");
FILE *df=fopen(dest,"a");
char ch,sl=0,ll=0;
while( (ch=fgetc(sf) )!=EOF  )
{
sl++;
if(ch=='\n')
{
if(sl>ll)
ll=sl;
}
}
rewind(sf);
char *s=calloc(ll+1,sizeof(char));
while(fgets(s,ll+1,sf))
fputs(s,df);
free(s);
s=0;
fclose(sf);
fclose(df);
}
