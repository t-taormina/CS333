/* Tyler Taormina - taormina@pdx.edu */
/* CS333 primesMT program - Lab 4*/

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

#define OPTIONS "t:u:vh"
//t - user defined number of threads
//u - upper bound prime numbers that are displayed
//v - verbose
//h - help

#define DEFAULT 100

BitBlock_t *bits = NULL;
pthread_t *threads = NULL;
unsigned short is_verbose = 0;
int num_threads = 1;
int array_size = 1;
uint32_t max_prime = DEFAULT;


int
check_verbose(void)
{
    if (is_verbose) {
        printf("verbose enabled\n");
    }
    return 0;
}

void
allocate_threads(void)
{    
    if (num_threads > 0) {
        threads = malloc(num_threads * sizeof(pthread_t));
    }
}

void free_threads(void)
{
    if (NULL != threads) {
        free(threads);
    }
}

void 
allocate_bits(void)
{
    if (max_prime > 0) {
        if (max_prime <= 32) {
            bits = malloc(array_size * sizeof(BitBlock_t));
        } else {
            array_size = (max_prime / 32) + 1;
            bits = malloc(array_size * sizeof(BitBlock_t));
        }
    }
}

void 
init_bits(void)
{
    uint32_t k;
    int i, index, bit_location;

    uint32_t mask = 0x1;

    for (i = 0; i < array_size; i++) {
        bits[i].bits = 0;
        //bits[i].mutex = PTHREAD_MUTEX_INITIALIZER;
    }

    // 0 & 1 are not prime so we mark them with a 1 (1 == not prime)
    bits[0].bits = mask | bits[0].bits;
    mask = 0x1 << 1;
    bits[0].bits = mask | bits[0].bits;

    /* Mark all even numbers as not prime */
    for (k = 4; k < max_prime; k++) {
        if (0 == k % 2) {
            index = k / 32;
            bit_location = k % 32;
            mask = 0x1 << (bit_location);
            bits[index].bits = mask | bits[index].bits;
        }
    }
}

void 
free_memory(void)
{
    if (NULL != bits) {
        free(bits);
        bits = NULL;
    }
}

void 
print_primes(void)
{
    int index, bit_location;
    uint32_t i;

    uint32_t mask = 0x0;

    if (NULL == bits) {
        return;
    }
    for (i = 0; i < max_prime; i++) {
        index = i / 32;
        bit_location = i % 32;
        mask = 0x1 << (bit_location);
        if (0 == (mask & bits[index].bits)){
            printf("%d\n", i);
        }
    }
    printf("\n");
}

void
sieve_of_eratosthenes(void)
{
    long tid, start;

    if (0 == num_threads) {
        return;
    }

    threads = malloc(num_threads * sizeof(pthread_t));

    start = 3;
    for (tid = 0; tid < num_threads; tid++) {
        pthread_create(&threads[tid], NULL, mark_bits, (void *) start);
        start += 2;
    }

    for (tid = 0; tid < num_threads; tid++) {
        pthread_join(threads[tid], NULL);
    }
}

void *
mark_bits(void *vid)
{
    int index, bit_location;
    uint32_t i, k;

    uint32_t mask = 0x1;
    long start = (long) (vid);

    for (i = start; i < max_prime; i += (num_threads * 2) ) {
        index = i / 32;
        bit_location = i % 32;
        mask = 0x1 << (bit_location);
        if (0 == (mask & bits[index].bits)) {
            for (k = i + 1; k < max_prime; k+= i) {
                if (0 == k % i) {
                    index = k / 32;
                    bit_location = k % 32;
                    mask = 0x1 << (bit_location);
                    bits[index].bits = mask | bits[index].bits;
                }
            }
        }
    }
    pthread_exit(EXIT_SUCCESS);
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
                    if (0 == num_threads) {
                        printf("You can't use 0 threads, defaulting to 1\n");
                        num_threads = 1;
                    }
                    // ignore for now
                    break;

                case 'u':
                    max_prime = atoi(optarg);
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
