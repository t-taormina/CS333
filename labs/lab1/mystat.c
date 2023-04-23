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
#include <sys/sysmacros.h>

#ifndef FASLE
# define FALSE      0
#endif // FALSE

#ifndef TRUE 
# define TRUE 1
#endif // TRUE

#define BUF_SIZE    50000
#define O_BUF       8
#define DNE         "DOES_NOT_EXIST"
#define PERM_MASK        000777

#ifdef NOISY_DEBUG
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG
      
int *conv_octal(int);
char *conv_omode(int*, char);

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

    printf("File: %s\n", argv[i]);

    printf("  File type:                ");
    char ld_mode;

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
                     char *buf;
                     ssize_t bufsize, nbytes;
                     bufsize = sb.st_size;
                     if (sb.st_size == 0) {
                       bufsize = BUF_SIZE;
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
                     if (strcmp(buf, DNE) == 0) {
                       printf("Symbolic link - with dangling destination\n");
                     }
                     else {
                       printf("Symbolic link -> %.*s\n", (int) nbytes, buf);
                     }
                     free(buf);
                     ld_mode = 'l';
                     break;

      default:       printf("unknown\n");                 break;
    }

    printf("  Device ID number:         %jxh/%jdd\n",
      (uintmax_t) minor(sb.st_dev),
      (uintmax_t) minor(sb.st_dev));
      //minor(sb.st_dev),
      //major(sb.st_dev));

    printf("  I-node number:            %ju\n", (uintmax_t) sb.st_ino);

    int *oct_mode;
    char *str_mode;
    uint octal = sb.st_mode & PERM_MASK;
    oct_mode = conv_octal(sb.st_mode);
    str_mode = conv_omode(oct_mode, ld_mode);
    //printf("  Mode:                     %s        (%d%d%d in octal)\n",
     //   str_mode, oct_mode[5], oct_mode[6], oct_mode[7]);
    printf("  Mode:                     %s        (%o in octal)\n", str_mode, octal);

    printf("  Link count:               %ju\n", (uintmax_t) sb.st_nlink);

    // Gather group and user info
    struct group *grp;
    grp = getgrgid(sb.st_gid);
    struct passwd *usr;
    usr = getpwuid(sb.st_uid);

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

    printf("  Last status change:       %s", ctime(&sb.st_ctime));
    printf("  Last file access:         %s", ctime(&sb.st_atime));
    printf("  Last file modification:   %s", ctime(&sb.st_mtime));
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

