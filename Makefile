CC = gcc
FLAGS += -Wall -g
PLIBS = array.o
CLIBS = -lfann -lm -L /usr/local/lib

all: parser.exe bestTrain.exe test.exe eval.exe

test.exe : test.c
	#
	### [Compiling] test.c ###
	$(CC) $(FLAGS) test.c -o test.exe $(CLIBS)

bestTrain.exe : bestTrain.c
	#
	### [Compiling] bestTrain.c ###
	$(CC) $(FLAGS) bestTrain.c -o bestTrain.exe $(CLIBS)

eval.exe : eval.c
	#
	### [Compiling] bestTrain.c ###
	$(CC) $(FLAGS) eval.c -o eval.exe $(CLIBS)

parser.exe: parser.c array.o parser.h
	#
	### [Compiling] parser.c ###
	$(CC) $(FLAGS) parser.c -o parser.exe $(PLIBS) $(CLIBS)

array.o: array.c array.h
	#
	### [Compiling] array.c ###
	$(CC) $(FLAGS) -c array.c -o array.o

clean:
	rm -f *.exe *.o
