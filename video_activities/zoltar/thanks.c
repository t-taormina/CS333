/* Tyler Taormina - taormina@pdx.edu */
/* Video Activity - t_hanks */

/* Compile with */
/*  gcc -Wall -o thanks thanks.c  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 4096
#define DEFAULT_PORT 10011
#define DEFAULT_SERVER "10.0.0.144" //my ip

int
main(int argc, char **argv)
{
    struct sockaddr_in server;
    socklen_t len = sizeof(struct sockaddr_in);
    char buf[BUF_SIZE] = "Big";
    ssize_t nbytes;
    int serv_soc;
    struct timeval tv;
    unsigned short port = DEFAULT_PORT;
    int is_verbose = 0;
    char server_name[100] = DEFAULT_SERVER;

    {
        int opt = -1;

        while ((opt = getopt(argc, argv, "s:p:vh")) != -1) {
            switch (opt) {
                case 's': 
                    // Destination, source
                    strcpy(server_name, optarg);
                    break;

                case 'p': 
                    sscanf(optarg, "%hu", &port);
                    break;

                case 'v':
                    is_verbose = !is_verbose;
                    break;

                case 'h':
                    printf("s - specify the server address\np - specify number of port\nv - verbose mode\nh - HELP\n");
                    break;

                default:
                    fprintf(stderr, "Usage: %s [-p port] [-s server_ip]\n", argv[0]);
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    if ((serv_soc = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket creation failure");
        exit(EXIT_FAILURE);
    }

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    
    if (setsockopt(serv_soc, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error on setsockopt");
        exit(EXIT_FAILURE); 
    }

    memset((char *) &server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, server_name, &server.sin_addr.s_addr);

    if (sendto(serv_soc, buf, strlen(buf), 0
                , (struct sockaddr *) &server, len) == -1) {
        perror("sendto error");
        exit(EXIT_FAILURE);
    }

    if ((nbytes = recvfrom(serv_soc, buf, BUF_SIZE, 0
                    , (struct sockaddr *) &server, &len)) == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("timeout\n");
            printf("The unfortunate server is not listening today\n");
            exit(EXIT_FAILURE);
        }
        else {
            perror("recvfrom() error");
            printf("The unfortunate server is ill today\n");
        }
    }

    buf[nbytes] = '\0';
    printf("My fortune for today\n%s\n", buf);
    
    return EXIT_SUCCESS;
}


