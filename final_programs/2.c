
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    pid_t pid = -1;
    int fd[2];

    if ((pipe(fd)) < 0) {
        perror("pipe error\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        char message[20] = "Howdy parent";
        close(fd[0]); // close read side of pipe
        write(fd[1], &message, (sizeof(message) + 1));
        _exit(EXIT_SUCCESS);
    }

    else {
        int stat_loc;
        char rec[20];
        pid = wait(&stat_loc);
        close(fd[1]); // close write side of pipe
        read(fd[0], &rec, (sizeof(rec) + 1));
        printf("%s\n     From child\n", rec);
    }
    return EXIT_SUCCESS;
}
