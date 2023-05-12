# Tyler Taormina - taormina@pdx.edu

CC = gcc
DEBUG = -g
DEFINES = 
CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
				 -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
				 -Wdeclaration-after-statement -Wextra $(DEFINES)
PROG1 = psush
PARSE = cmd_parse.c
PROGS = $(PROG1)  
INCLUDES = cmd_parse.h


all: $(PROGS)

$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) $(PARSE) -o $@ $^

$(PROG1).o: $(PROG1).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean cls: 
	rm -f $(PROGS) *.o *~ \#*

tar: 
	tar cvfa bin_files_taormina.tar.gz *.[ch] [mM]akefile
open: 
	nvim *.c *.h Makefile -p
