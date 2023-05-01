// gcc -Wall fibr.c -o fibr
// Tyler Taormina - taormina@pdx.edu
// CS333 Video Assignment 1

#include <stdio.h>
#include <stdlib.h>


unsigned long fib(unsigned long);

int 
main(int argc, char **argv) 
{
	unsigned long n = 0;

	if (argc < 2) {
		printf("Must give value on command line.\n");
		exit(EXIT_FAILURE);
	}
	n = atol(argv[1]);

	if (n > 93 || n < 1) {
		printf("Enter a number between 1 and 93(inclusive)\n");
		exit(EXIT_FAILURE);
	}

	printf("%5d: %lu\n", 0, 0ul);
	printf("%5d: %lu\n", 1, 1ul);
	
	for (unsigned long i = 2; i <= n; i++) {
		printf("%5ld: %lu\n", i, fib(i));
	}
	exit(EXIT_SUCCESS);
}

unsigned long 
fib (unsigned long n) 
{
	if (n <= 1) {
		return n;
	}
	return fib(n-1) + fib(n-2);
}

