/* Tyler Taormina - taormina@pdx.edu */
/* Video Activity - zoltar */

/* Compile with */
/*  gcc -Wall -o zoltar zoltar.c  */

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
#define FORTUNE_PATH "/usr/local/bin/hello"

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
                    break;

                default:
                    fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
        perror("bind failure");
        exit(EXIT_FAILURE);
    }

    if (is_verbose > 0) {
        printf("Listening for requests on port %hu\n", port);
    }

    sprintf(fortune_cmd, "%s -n %d", FORTUNE_PATH, BUF_SIZE - 1);
    while ((nbytes = recvfrom(socketfd, buf, BUF_SIZE, 0
                    , (struct sockaddr *) &cliaddr, &addrlen)) != -1) {

        if (is_verbose > 0) {
            printf("Request from %s: %d\n"
                    , inet_ntoa(cliaddr.sin_addr)
                    , ntohs(cliaddr.sin_port));
        }
        memset(reply, 0, sizeof(reply));
        fp = popen(fortune_cmd, "r");
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            strcat(reply, buf);
        }
        pclose(fp);
        sendto(socketfd, reply, strlen(reply), 0
                , (struct sockaddr *) &cliaddr, addrlen);
    }

    if (is_verbose > 0) {
        printf("Sent fortune:\n%s\n", reply);
    }
    close(socketfd);

    return EXIT_SUCCESS;
}
