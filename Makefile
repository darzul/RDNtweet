CC = gcc
FLAGS += -Wall -g
CLIBS = array.o fonction.o

all: parser.exe

parser.exe: array.o fonction.o
	### [Compiling] parser.c ###
	$(CC) $(FLAGS) parser.c -o parser.exe $(CLIBS)

array.o:
	### [Compiling] array.c ###
	$(CC) $(FLAGS) -c array.c -o array.o

fonction.o:
	### [Compiling] fonction.c ###
	$(CC) $(FLAGS) -c fonction.c -o fonction.o

clean:
	rm *.exe *.o
