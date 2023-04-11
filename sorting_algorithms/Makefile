CC = gcc -Wall -g 
OBJECTS = main.o sort.o

all: sort

sort : $(OBJECTS)
	$(CC) -o sort $(OBJECTS)

main.o : main.c
	$(CC) -c main.c

sort.o : sort.c
	$(CC) -c sort.c

clean :
	rm sort $(OBJECTS)
