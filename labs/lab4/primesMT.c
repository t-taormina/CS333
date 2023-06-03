/* Tyler Taormina - taormina@pdx.edu */
/* CS333 primesMT program - Lab 4*/
/* Credits: rchaney@pdx.edu*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdint.h>
//#include <sys/param.h>

#include "sieveOE.h"

#define OPTIONS "t:u:hv"
//t - user defined number of threads
//u - upper bound prime numbers that are displayed
//v - verbose
//h - help

extern unsigned short is_verbose;

int 
main( int argc, char *argv[] )
{
    
    {
        int opt = -1;
        while ((opt = getopt(argc, argv, "t:d:h")) != -1) {
            switch (opt) {
                case 't': 
                    //num_threads = atoi(optarg);
                    // ignore for now
                    break;

                case 'u':
                    //dim = atoi(optarg);
                    break;

                case 'h':
                    printf("%s: -t # -d #\n", argv[0]);
                    printf("\t-t #: number of threads\n");
                    printf("\t-u #: upper bound for prime numbers displayed\n");
                    exit(0);
                    break;

                default: /* '?' */
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }


    printf("hello, world!\n");
    return EXIT_SUCCESS;
}
