CC = gcc
DEBUG = -g
DEFINES = 
CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
				 -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
				 -Wdeclaration-after-statement -Wextra $(DEFINES)
PROG1 = bin_write
PROG2 = 
PROG3 = 
PROG4 = 
PROGS = $(PROG1) $(PROG2) $(PROG3) $(PROG4) 
INCLUDES = bin_file.h

all: $(PROGS)

$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) -o $@ $^

$(PROG1).o: $(PROG1).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean cls: 
	rm -f $(PROGS) *.o *~ \#*

tar: 
	tar cvfa bin_files_${LOGNAME}.tar.gz *.[ch] [mM]akefile
