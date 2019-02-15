
sh: qkshell.o history.o path.o
	gcc qkshell.o history.o path.o -o sh

qkshell.o: qkshell.c
	gcc qkshell.c -o qkshell.o -c

history.o: history.c history.h
	gcc history.c -o history.o -c

path.o: path.c path.h
	gcc path.c -o path.o -c

clean:
	rm *.o sh history.txt
