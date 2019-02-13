
sh: qkshell.o history.o
	gcc qkshell.o history.o -o sh

qkshell.o: qkshell.c
	gcc qkshell.c -o qkshell.o -c

history.o: history.c history.h
	gcc history.c -o history.o -c

clean:
	rm *.o sh history.txt
