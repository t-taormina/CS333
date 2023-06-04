/* Tyler Taormina - taormina@pdx.edu */
/* CS333 primesMT program - Lab 4*/
/* Credits: rchaney@pdx.edu*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include "sieveOE.h"

#define OPTIONS "t:u:hv"
#define DEFAULT 100

unsigned short is_verbose = 0;
int num_threads = 1;
int array_size = 1;
int max_prime = DEFAULT;


int
check_verbose(void)
{
    if (is_verbose) {
        printf("verbose enabled\n");
    }
    return 0;
}

BitBlock_t *
allocate_bits(void)
{
    BitBlock_t *temp_bits = NULL;

    if (max_prime <= 0) {
        return temp_bits;
    }
    if (max_prime <= 32) {
        temp_bits = malloc(array_size * sizeof(BitBlock_t));
    } else {
        array_size = (max_prime / 32) + 1;
        temp_bits = malloc(array_size * sizeof(BitBlock_t));
        //printf("array size: %d\n", array_size);
    }
    return temp_bits;
}

void 
init(BitBlock_t *arr)
{
    int i;
    for (i = 0; i < array_size; i++) {
        arr[i].bits = 0;
    }
}

void 
free_memory(BitBlock_t *arr)
{
    if (NULL != arr) {
        free(arr);
        arr = NULL;
    }
}

void 
print_bits(BitBlock_t *arr)
{
    if (NULL == arr) {
        return;
    }
    for (int i = 0; i < array_size; i++) {
        printf("%d\n", arr[i].bits);
    }
    printf("\n");
}

int 
process_cmd_line(int argc, char **argv)
{
    {
        int opt = -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
                case 't': 
                    num_threads = atoi(optarg);
                    // ignore for now
                    printf("\t-t #: number of threads\n");
                    printf("Num threads entered: %d\n", num_threads);
                    break;

                case 'u':
                     max_prime = atoi(optarg);
                    // ignore for now
                    printf("\t-u #: display prime numbers <= argument passed\n");
                    printf("max prime entered: %d\n", max_prime);
                    break;

                case 'h':
                    printf("%s: -t # -u #\n", argv[0]);
                    printf("\t-t #: number of threads\n");
                    printf("\t-u #: display prime numbers <= argument passed\n");
                    printf("\t-v: enable verbose mode\n");
                    exit(0);
                    break;

                case 'v':
                    // Increasable verbosity to display different information
                    is_verbose++;
                    if (is_verbose) {
                        fprintf(stderr, "verbose: verbose option selected: %d\n"
                                , is_verbose);
                    }
                    break;

                default: /* '?' */
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }
    return 0;
}
