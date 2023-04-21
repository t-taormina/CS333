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
# define FALSE 0
#endif // FALSE

#ifndef TRUE 
# define TRUE 1
#endif // TRUE

#define BUF_SIZE 50000
#define DNE "DOES_NOT_EXIST"

#ifdef NOISY_DEBUG
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG
      
int *conv_octal(int);

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

    switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:  printf("block device\n");            break;
      case S_IFCHR:  printf("character device\n");        break;
      case S_IFDIR:  printf("directory\n");               break;
      case S_IFIFO:  printf("FIFO/pipe\n");               break;
      case S_IFREG:  printf("regular file\n");            break;
      case S_IFSOCK: printf("socket\n");                  break;
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
                                                          break;

      default:       printf("unknown\n");                 break;
    }

    printf("  Device ID number:         %jxh/%jdd\n",
      (uintmax_t) minor(sb.st_dev),
      (uintmax_t) minor(sb.st_dev));
      //minor(sb.st_dev),
      //major(sb.st_dev));

    printf("  I-node number:            %ju\n", (uintmax_t) sb.st_ino);

    int *omode;
    omode = conv_octal(sb.st_mode);
    printf("  Mode:                     (%d%d%d in octal)\n",
        omode[5], omode[6], omode[7]);

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
  static int nums[8];
  int i, j;
  for (i = 0, j = 7; number > 0; ++i) {
    nums[j-i] = number % 8;
    number = number / 8;
  }
  return nums;
}


