#include"header.h"
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
