CC = gcc -Wall -g 
MYSTAT = mystat.o 
MYWC = mywc.o

all: mystat mywc

mystat: $(MYSTAT)
	$(CC) -o mystat $(MYSTAT)

mywc: $(MYWC)
	$(CC) -o mywc $(MYWC)

mystat.o : mystat.c
	$(CC) -c mystat.c

mywc.o : mywc.c
	$(CC) -c mywc.c

clean :
	rm mystat mywc $(MYWC) $(MYSTAT)

open : 
	vim *.c  Makefile -p

