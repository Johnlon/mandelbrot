CC = gcc -std=c9x -g -DHAVE_AOS4 #-fsanitize=address #-DHAVE_ECPP -DHAVE_MISRA
LDFLAGS = -lm

TARGET=g

all: 
	mkdir -p bin
	$(CC) integer.c -o bin/integer
	$(CC) float.c -o bin/float
	$(CC) squareUsingBytes.c squareUsingBytesTest.c -o bin/squareUsingBytesTest

clean: 
	rm -r bin

