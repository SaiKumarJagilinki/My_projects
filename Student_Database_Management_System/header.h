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
