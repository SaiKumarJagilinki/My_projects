#include"header.h"
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
//add_main("task3.c","my_src.i");
include_header("task3.c","my_src.i");
remove("task1.c");
remove("task2.c");
remove("task3.c");
}
