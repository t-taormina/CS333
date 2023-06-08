/* Tyler Taormina - taormina@pdx.edu */ /* CS333 primesMT program - Lab 4*/

#pragma once

#ifndef _SIEVEOE_H
# define _SIEVEOE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>


typedef struct BitBlock_s {
    uint32_t bits;
    pthread_mutex_t mutex;
} BitBlock_t; 

int check_verbose(void);
int process_cmd_line(int , char **);
void allocate_bits(void);
void allocate_threads(void);
void init_bits(void);
void free_memory(void);
void print_primes(void);
void *mark_bits(void *);
void sieve_of_eratosthenes(void);
#endif // _SIEVEOE_H
