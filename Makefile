CC = gcc
FLAGS += -Wall -g
PLIBS = array.o
CLIBS = -lfann -lm -L /usr/local/lib

all: parser.exe bestTrain.exe test.exe

test.exe :
	#
	### [Compiling] test.c ###
	$(CC) $(FLAGS) test.c -o test.exe $(CLIBS)

bestTrain.exe :
	#
	### [Compiling] bestTrain.c ###
	$(CC) $(FLAGS) bestTrain.c -o bestTrain.exe $(CLIBS)

parser.exe: array.o
	#
	### [Compiling] parser.c ###
	$(CC) $(FLAGS) parser.c -o parser.exe $(PLIBS)

array.o:
	#
	### [Compiling] array.c ###
	$(CC) $(FLAGS) -c array.c -o array.o

clean:
	rm -f *.exe *.o
