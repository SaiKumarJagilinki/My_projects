#include"header.h"
void add_main(char*task3,char*exe)
{
FILE *sf=fopen(task3,"r");
FILE *df=fopen(exe,"a");
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
char *str=calloc(ll+1,sizeof(char));
rewind(sf);
while(fgets(str,ll+1,sf))
fputs(str,df);
fclose(sf);
fclose(df);
}
void replace_macro(char*src,char*dest)
{
FILE *sf=fopen(src,"r");
FILE *df=fopen(dest,"w");
char ch;
macro m[100];
int sl=0,ll=0;
while( (ch=fgetc(sf))!=EOF )
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
char *str=calloc(ll+1,sizeof(char));

int i=0,mlen=0;
while(fgets(str,ll+1,sf))
{
if(strstr(str,"main()"))
{
fputs(str,df);
break;
}
if(strstr(str,"#define "))
{
sscanf(str+strlen("#define "),"%s %[^\n]",m[i].old,m[i].new);
i++;
}
}
mlen=i;

char t[ll],*q;
while(fgets(str,ll+1,sf))
{
for(i=0;i<mlen;i++)
{
if(q=strstr(str,m[i].old))
{
strcpy(t,q+strlen(m[i].old));
strcpy(q,m[i].new);
strcpy(q+strlen(m[i].new),t);
}
}
fputs(str,df);
}
fclose(sf);
fclose(df);
}
