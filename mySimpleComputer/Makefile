#Makefile

main: clean main.o libSimpleComputer.a
	gcc -o main main.o -L. -lSimpleComputer

main.o: main.c
	gcc -c main.c

libSimpleComputer.a: mySimpleComputer.o
	ar r libSimpleComputer.a mySimpleComputer.o

mySimpleComputer.o: mySimpleComputer.c
	gcc -c mySimpleComputer.c

clean:
	rm -f *.o *.a
