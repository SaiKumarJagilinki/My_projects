CC=gcc   
target=main.o Task1.o Task2.o Task3.o

my_preprocessor:${target}
	${CC} ${target} -o my_preprocessor

main.o:main.c
	${CC} -c main.c
Task1.o:Task1.c
	${CC} -c Task1.c
Task2.o:Task2.c
	${CC} -c Task2.c
Task3.o:Task3.c
	${CC} -c Task3.c
clear:
	@echo "cleaning up...."
	@rm -vr *.o


