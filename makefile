CFLAGS= -g

sh: qkshell.o history.o path.o
	gcc $(CFLAGS) qkshell.o history.o path.o -o sh

qkshell.o: qkshell.c
	gcc $(CFLAGS) qkshell.c -o qkshell.o -c

history.o: history.c history.h
	gcc $(CFLAGS) history.c -o history.o -c

path.o: path.c path.h
	gcc $(CFLAGS) path.c -o path.o -c

clean:
	rm *.o sh history.txt
