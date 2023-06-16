
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    pid_t pid = -1;
    int fd[2];
    char message[20] = "Howdy parent";
    char rec[20];

    for (int i = 0; i < 2; i++) {
        if ((pipe(fd + i)) < 0) {
            perror("pipe error\n");
            exit(EXIT_FAILURE);
        }
    }

    if ((pid = fork()) == -1) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if ((dup2(fd[1], STDOUT_FILENO)) < 0) {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < 2; i++) {
            close(fd[i]);
        }

        write(stdout, &message, strlen(message));
        _exit(EXIT_SUCCESS);
    }

    else {
        wait(pid);
        if ((dup2(fd[0], STDIN_FILENO)) < 0) {
            perror("dup2 error");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < 2; i++) {
            close(stdin, );
        }

        read(stdout, rec, strlen(rec));
    }
    return EXIT_SUCCESS;

}
