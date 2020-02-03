all: SHELL379

SHELL379: SHELL379.o commands.o
	gcc -ggdb -Wall -std=c99 -o SHELL379 SHELL379.o commands.o

SHELL379.o:
	gcc -ggdb -Wall -std=c99 -c SHELL379.c

commands.o: commands.c commands.h
	gcc -g -Wall -std=c99 -c commands.c

clean:
	rm SHELL379 SHELL379.o commands.o
