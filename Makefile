CC = gcc
FLAGS += -Wall -g
CLIBS = array.o
FANN = -lfann -lm -L/usr/local/lib

all: parser.exe build_RDN.exe

parser.exe: array.o
	#
	### [Compiling] parser.c ###
	$(CC) $(FLAGS) parser.c -o parser.exe $(CLIBS)

array.o:
	#
	### [Compiling] array.c ###
	$(CC) $(FLAGS) -c array.c -o array.o

build_RDN.exe:
	#
	### [Compiling] build_RDN_tweet.c ###
	$(CC) $(FLAGS) $(FANN) build_RDN.c -o build_RDN.exe

clean:
	rm *.exe *.o
