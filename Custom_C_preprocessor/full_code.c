#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void remove_comments(char*,char*);
void search_inc_header(char*,char*);
void include_header(char*,char*);
void add_main(char*,char*);
void replace_macro(char*,char*);
typedef struct 
{
char old[100];
char new[100];
}macro;
void main(int argc,char**argv)
{
if(argc!=2)
{
printf("usage:./a.out file\n");
return;
}
remove_comments(argv[1],"task1.c");
search_inc_header("task1.c","task2.c");//task2=including header files except main fn
remove_comments("task2.c","my_src.i");// removing comments in task2 file copy into .i file
replace_macro("task1.c","task3.c");//task3= including only main file replaced with macro
add_main("task3.c","my_src.i");
remove("task1.c");
remove("task2.c");
remove("task3.c");
}
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
while( (ch2=fgetc(sf))!=EOF  )    
{
if(ch1=='*'&&ch2=='/')
break;
ch1=ch2;
}
    }
}
else
fputc(ch1,df);
}
fclose(sf);
fclose(df);
}
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

char t[100],*q;
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
