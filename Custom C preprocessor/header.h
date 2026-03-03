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
