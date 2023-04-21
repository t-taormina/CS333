CC = gcc -Wall -g 
OBJECTS = mystat.o 

all: mystat 

mystat: $(OBJECTS)
	$(CC) -o mystat $(OBJECTS)

mystat.o : mystat.c
	$(CC) -c mystat.c

clean :
	rm mystat $(OBJECTS)

open : 
	vim *.c Makefile -p

