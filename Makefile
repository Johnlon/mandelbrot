CC = gcc -std=c9x -g -DHAVE_AOS4 #-fsanitize=address #-DHAVE_ECPP -DHAVE_MISRA
LDFLAGS = -lm

TARGET=g

all: squareUsingBytes integer float

clean: squareUsingBytes integer float
	rm squareUsingBytes integer float
