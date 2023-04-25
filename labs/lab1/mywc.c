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
//             {line , word , char,  file }
int flags[4] = {FALSE, FALSE, FALSE, FALSE};
int flag_passed = FALSE;

static int is_verbose = FALSE;

int read_data(FILE *, count_t *);
int output_data(FILE *, count_t  *, int, int *, char *);

int 
main(int argc, char **argv) 
{
  FILE *ifile = stdin;
  FILE *ofile = stdout;
  count_t ct;
  char file[BUFSIZ];
  {
    int opt = 0;
    NOISY_DEBUG_PRINT;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
      switch (opt) {
        case 'c': 
          flags[2] = TRUE;
          flag_passed = TRUE;
          break;
        case 'l': 
          flags[0] = TRUE;
          flag_passed = TRUE;
          break;
        case 'w':
          flags[1] = TRUE;
          flag_passed = TRUE;
          break;
        case 'f':
          ifile = fopen(optarg, "r");
          if (ifile == NULL) {
            perror("open of input file failed");
            exit(EXIT_FAILURE);
          }
          strcpy(file, optarg);
          flags[3] = TRUE;
          flag_passed = TRUE;
          break;
        case 'h':
          fprintf(ofile, "%s\n", argv[0]);
          fprintf(ofile, "        options: clf:hv\n");
          fprintf(ofile, "        -c      : display the number of characters in the input\n");
          fprintf(ofile, "        -l      : display the number of lines in the input\n");
          fprintf(ofile, "        -w      : display the number of words in the input\n");
          fprintf(ofile, "        -f file : use file as input, defaults to stdin\n");
          fprintf(ofile, "        -h      : display a command options and exit\n");
          fprintf(ofile, "        -v      : give LOTS of gross verbose trace output to stderr.\n");
          break;
        case 'v':
          is_verbose = !is_verbose;
          break;
        default: 
          fprintf(stderr, "invalid option\n");
          exit(EXIT_FAILURE);
      }
    }
    NOISY_DEBUG_PRINT;
  }

  read_data(ifile, &ct);
  NOISY_DEBUG_PRINT;
  if (is_verbose) {
    fprintf(stderr, "input file processed\n");
  }

  output_data(ofile, &ct, flag_passed, flags, file);
  NOISY_DEBUG_PRINT;
  if (is_verbose) {
    fprintf(stderr, "output data complete\n");
  }
 
  if (ifile != stdin) {
    fclose(ifile);
  }
  if (is_verbose) {
    fprintf(stderr, "closing input file\n");
  }
  if (ofile != stdout) {
    fclose(ofile);
  }
  if (is_verbose) {
    fprintf(stderr, "closing output file\n");
  }
  exit(EXIT_SUCCESS);
}

int
read_data(FILE *ifile, count_t *ct)
{
  char buffer[BUF_SIZE] = {0};
  NOISY_DEBUG_PRINT;
  while (fgets(buffer, BUF_SIZE, ifile) != NULL) {
    ct->l += 1;
    char *token = NULL;
    token = strtok(buffer, DELIMITERS);
    while(token) {
      ct->w += 1;
      int char_ct = strlen(token) + 1;
      ct->c += char_ct;
      token = strtok(NULL, DELIMITERS);
    }
  }
  return 0;
}

int
output_data(FILE *ofile, count_t  *ct, int fpass, int *flags, char *file)
{
  if (fpass == FALSE) {
    // default print all data
    fprintf(ofile, "%d %d %d\n", ct->l, ct->w, ct->c); 
  }
  if (flags[3] == TRUE && flags[0] == FALSE && flags[1] == FALSE && flags[2] == FALSE) {
    fprintf(ofile, "%d %d %d %s\n", ct->l, ct->w, ct->c, file); 
  }

  else {
    if (flags[0] == TRUE) { fprintf(ofile, "%d ", ct->l); }
    if (flags[1] == TRUE) { fprintf(ofile, "%d ", ct->w); }
    if (flags[2] == TRUE) { fprintf(ofile, "%d ", ct->c); }
    if (flags[3] == TRUE) { fprintf(ofile, "%s ", file);  }
  }
  return 0;
}
