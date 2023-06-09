/* Tyler Taormina - taormina@pdx.edu */
/* Video Activity - zoltar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 4096
#define DEFAULT_PORT 10011
#define FORTUNE_PATH "/usr/games/fortune"

int
main(int argc, char **argv)
{
    char buf[BUF_SIZE] = {'\0'};
    char reply[BUF_SIZE] = {'\0'};
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    ssize_t nbytes = 0;
    int socketfd = -1;
    int is_verbose = 0;
    FILE *fp = NULL;
    char fortune_cmd[100] = {'\0'};
    unsigned short port = DEFAULT_PORT;

    {
        int opt = -1;
        while ((opt = getopt(argc, argv, "p:vh")) != -1) {
            switch (opt) {
                case 'p':
                    sscanf(optarg, "%hu", &port);
                    break;

                case 'v': 
                    is_verbose = !is_verbose;
                    break;

                case 'h':
                    printf("p - specify number of ports\nv - verbose mode\nh - HELP\n");

            }
        }
    }

    return EXIT_SUCCESS;
}
