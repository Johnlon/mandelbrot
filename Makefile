CC = gcc -std=c9x -g -DHAVE_AOS4 #-fsanitize=address #-DHAVE_ECPP -DHAVE_MISRA
LDFLAGS = -lm

TARGET=g

all: 
	mkdir -p bin
	$(CC) integer.c -o bin/integer
	$(CC) float.c -o bin/float
	$(CC) fixedPointMultUsingBytes.c fixedPointMultUsingBytesTest.c -o bin/fixedPointMultUsingBytesTest

clean: 
	rm -r bin

