// Tyler Taormina - taormina@pdx.edu
// CS333 Lab 1 - mywc

#include <stdio.h>
#include <stdlib.h> // for exit()
#include <unistd.h> // for getopt()
#include <string.h>

#define OPTIONS "clwf:hv"

#ifndef FASLE
# define FALSE 0
#endif // FALSE

#ifndef TRUE 
# define TRUE 1
#endif // TRUE

#define BUF_SIZE 50000
#define DELIMITERS " \n"

#ifdef NOISY_DEBUG
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG

typedef struct count_s {
  int c;
  int w;
  int l;
} count_t;

static int is_verbose = FALSE;

int read_data(FILE *, count_t *);
int output_data(FILE *, count_t  *);
//3 different output functions for each flag
// look if order of flags changes order of output

int 
main(int argc, char **argv) 
{
  FILE *ifile = stdin;
  FILE *ofile = stdout;
  count_t ct;
  read_data(ifile, &ct);
  output_data(ofile, &ct);
  exit(EXIT_SUCCESS);
}

int
read_data(FILE *ifile, count_t *ct)
{
  //char buffer[BUF_SIZE] = {0};
  //  while fgets returns valid info increment line count
  //  use delimiters to seperate words and increment word count
  //  use strlen on each word to increment character count
  return 0;
}

int
output_data(FILE *ofile, count_t  *ct)
{
  return 0;
}
