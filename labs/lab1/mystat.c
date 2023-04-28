// Tyler Taormina - taormina@pdx.edu
// CS333 Lab 1 - mystat

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include "sysmacros.h"

#ifndef  FASLE
# define FALSE       0
#endif// FALSE

#ifndef  TRUE 
# define TRUE        1
#endif //TRUE

#define O_BUF        8
#define DNE          "DOES_NOT_EXIST"
#define P_MASK       000777

#ifdef   NOISY_DEBUG
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif// NOISY_DEBUG
      
int     *conv_octal(int);
char    *conv_omode(int*, char);
void    conv_wday(int, char*);

int
main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; ++i) {
    struct stat sb;
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat\n");
      exit(EXIT_FAILURE);
    }

    char ld_mode = '\0';
    char *buf = NULL;
    ssize_t bufsize, nbytes;
    printf("File: %s\n", argv[i]);
    printf("  File type:                ");

    // Handle file type
    switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:  printf("block device\n");            
                     ld_mode = 'b';
                     break;
      case S_IFCHR:  printf("character device\n");        
                     ld_mode = 'c';
                     break;
      case S_IFDIR:  printf("directory\n");               
                     ld_mode = 'd';
                     break;
      case S_IFIFO:  printf("FIFO/pipe\n");               
                     ld_mode = 'p';
                     break;
      case S_IFREG:  printf("regular file\n");
                     ld_mode = '-';
                     break;
      case S_IFSOCK: printf("socket\n");
                     ld_mode = 's';
                     break;
      case S_IFLNK:
                     bufsize = sb.st_size;
                     if (sb.st_size == 0) {
                       bufsize = BUFSIZ;
                     }
                     buf = malloc(bufsize);
                     if (buf == NULL) {
                       perror("malloc");
                       exit(EXIT_FAILURE);
                     }
                     nbytes = readlink(argv[i], buf, bufsize);
                     if (nbytes == -1) {
                       perror("readlink");
                       exit(EXIT_FAILURE);
                     }
                     //if(nbytes == -1) {
                     if (strcmp(buf, DNE) == 0) {
                       printf("Symbolic link - with dangling destination\n");
                     }
                     else {
                       printf("Symbolic link -> %.*s\n", (int) nbytes, buf);
                     }
                     free(buf);
                     ld_mode = 'l';
                     break;

      default:       
                     printf("unknown\n");
                     break;
    }

    // Handle device ID
    printf("  Device ID number:         %jxh/%jdd\n",
      (uintmax_t) minor(sb.st_dev),
      (uintmax_t) minor(sb.st_dev));
    printf("  I-node number:            %ju\n", (uintmax_t) sb.st_ino);

    // Handle st_mode data
    int      *oct_mode;
    char     *str_mode;
    uintmax_t octal;

    octal    = sb.st_mode & P_MASK;
    oct_mode = conv_octal(sb.st_mode);
    str_mode = conv_omode(oct_mode, ld_mode);
    printf("  Mode:                     %s        (%03jo in octal)\n",
        str_mode, octal);
    printf("  Link count:               %ju\n", (uintmax_t) sb.st_nlink);

    // Gather group and user info
    struct group  *grp;
    struct passwd *usr;
    grp    =      getgrgid(sb.st_gid);
    usr    =      getpwuid(sb.st_uid);

    printf("  Owner Id:                 %s           (UID = %d)\n",
          usr->pw_name, usr->pw_uid);
    printf("  Group Id:                 %s              (GID = %d)\n",
          grp->gr_name, grp->gr_gid);

    printf("  Preferred I/O block size: %jd bytes\n",
        (intmax_t) sb.st_blksize);
    printf("  File size:                %jd bytes\n",
        (intmax_t) sb.st_size);
    printf("  Blocks allocated:         %jd\n",
        (intmax_t) sb.st_blocks);

    // Handle time output
    struct    tm *tm;
    char      timestr[BUFSIZ];

    // Access time
    if ((tm = localtime(&sb.st_atime)) == NULL)
      exit(EXIT_FAILURE);
    if (strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S %z (%Z) %a (local)",
          tm) == 0)
      exit(EXIT_FAILURE);
    printf("  Last file access:         %s\n", timestr);
  
    // Modification time
    if ((tm = localtime(&sb.st_mtime)) == NULL)
      exit(EXIT_FAILURE);
    if (strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S %z (%Z) %a (local)",
          tm) == 0)
      exit(EXIT_FAILURE);
    printf("  Last file modification:   %s\n", timestr);

    // Status time
    if ((tm = localtime(&sb.st_ctime)) == NULL)
      exit(EXIT_FAILURE);
    if (strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S %z (%Z) %a (local)",
          tm) == 0)
      exit(EXIT_FAILURE);
    printf("  Last status change:       %s\n", timestr);
  }
  exit(EXIT_SUCCESS);
}

int 
*conv_octal(int number)
{
  static int nums[O_BUF];
  int i, j;
  for (i = 0, j = 7; number > 0; ++i) {
    nums[j-i] = number % 8;
    number = number / 8;
  }
  return nums;
}

char 
*conv_omode(int *arr, char lead)
{
  static char str_mode[10];
  str_mode[0] = lead;
  int i, j;
  for (i = 5; i < O_BUF; ++i) {
    if (i == 5) j = 1;
    if (i == 6) j = 4;
    if (i == 7) j = 7;
    switch (arr[i]) {
      case 0:
        str_mode[j] =   '-';
        str_mode[j+1] = '-';
        str_mode[j+2] = '-';
        break;
      case 1:
        str_mode[j] =   '-';
        str_mode[j+1] = '-';
        str_mode[j+2] = 'x';
        break;
      case 2:
        str_mode[j] =   '-';
        str_mode[j+1] = 'w';
        str_mode[j+2] = '-';
        break;
      case 3:
        str_mode[j] =   '-';
        str_mode[j+1] = 'w';
        str_mode[j+2] = 'x';
        break;
      case 4:
        str_mode[j] =   'r';
        str_mode[j+1] = '-';
        str_mode[j+2] = '-';
        break;
      case 5:
        str_mode[j] =   'r';
        str_mode[j+1] = '-';
        str_mode[j+2] = 'x';
        break;
      case 6:
        str_mode[j] =   'r';
        str_mode[j+1] = 'w';
        str_mode[j+2] = '-';
        break;
      case 7:
        str_mode[j] =   'r';
        str_mode[j+1] = 'w';
        str_mode[j+2] = 'x';
        break;
      default: break;
    }
  }
  return str_mode;
}
