# Tyler Taormina - taormina@pdx.edu

CC = gcc
DEBUG = -g
DEFINES = 
CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
				 -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
				 -Wdeclaration-after-statement -Wextra $(DEFINES)
PROG1 = psush
PROG2 = cmd_parse

PROGS = $(PROG1)  
INCLUDES = cmd_parse.h


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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./psush

tar: 
	tar cvfa bin_files_taormina.tar.gz *.[ch] [mM]akefile

open: 
	nvim *.c *.h Makefile -p
