#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "bin_file.h"

#define OPTIONS "g:G:F:"
int 
main(int argc, char **argv)
{
  char *g_name = NULL;
  char *f_name = NULL;
  int ofd = -1;
  double gpa = -1.0;
  bin_file_t student;
  off_t size = sizeof(bin_file_t);
  {
    int opt = 0;
    while((opt = getopt(argc, argv, OPTIONS)) != -1) {
      switch(opt) {
        case 'g': 
          if (sscanf(optarg, "%lf", &gpa) != 1) {
            perror("cannot parse gpa");
            exit(EXIT_FAILURE);
          }
          break;
        case 'G':
          g_name = optarg;
          break;
        case 'F':
          f_name = optarg;
          break;
        default:
          fprintf(stderr, "unknown option passed %c\n", opt);
          exit(EXIT_FAILURE);
          break;
      }
    }
  }

  if((gpa < 0) || (g_name == NULL) || (f_name == NULL)) {
    fprintf(stderr, "must specify gpa(double), given name(string), and family name(string)");
    exit(EXIT_FAILURE);
  }
  ofd = open(FILE_NAME, O_RDWR | O_APPEND); // OPENED

  if(ofd < 0) {
    perror("cannot open " FILE_NAME " for output");
    exit(EXIT_FAILURE);
  }
  lseek(ofd, -size, SEEK_END);
  read(ofd, &student, sizeof(bin_file_t));
  student.id += 1;
  strcpy(student.g_name, g_name);
  strcpy(student.f_name, f_name);
  write(ofd, &student, sizeof(bin_file_t));
 
  close(ofd); // CLOSED
              
  return EXIT_SUCCESS;
}

