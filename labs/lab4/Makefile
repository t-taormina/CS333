# Tyler Taormina - taormina@pdx.edu

CC = gcc
DEBUG = -g
DEFINES = 
PTHREAD = -pthread
CFLAGS = $(DEBUG) -Wall -Wshadow -Wextra -Wunreachable-code -Wredundant-decls \
		-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
		-Wdeclaration-after-statement -Wno-return-local-addr \
		-Wunsafe-loop-optimizations -Wuninitialized $(PTHREAD)

PROG1 = primesMT
PROG2 = sieveOE
PROGS = $(PROG1)  

INCLUDES = sieveOE.h

all: $(PROGS)

$(PROG1): $(PROG1).o $(PROG2).o
	$(CC) $(CFLAGS) -o $@ $^

$(PROG1).o: $(PROG1).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

$(PROG2).o: $(PROG2).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean cls: 
	rm -f $(PROGS) *.o *~ \#*

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./primesMT

tar: 
	tar cvfa taormina_lab4_cs333.tar.gz *.[ch] [mM]akefile

open: 
	vim *.c *.h Makefile -p
