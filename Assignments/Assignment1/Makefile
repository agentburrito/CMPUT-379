all: SHELL379

SHELL379: SHELL379.o commands.o helper.o
	gcc -ggdb -Wall  -o SHELL379 SHELL379.o commands.o helper.o

SHELL379.o:
	gcc -ggdb -Wall  -c SHELL379.c

commands.o: commands.c commands.h
	gcc -ggdb -Wall  -c commands.c

helper.o: helper.c helper.h
	gcc -ggdb -Wall -c helper.c
clean:
	rm SHELL379 SHELL379.o commands.o helper.o
