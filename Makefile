CC = gcc -std=c9x -g -DHAVE_AOS4 #-fsanitize=address #-DHAVE_ECPP -DHAVE_MISRA
LDFLAGS = -lm

TARGET=g

all: h

h: h.c
	$(CC) h.c -o h

