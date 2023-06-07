/* Tyler Taormina - taormina@pdx.edu */
/* CS333 primesMT program - Lab 4 */

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

extern unsigned short is_verbose;

int 
main( int argc, char **argv)
{

    process_cmd_line(argc, argv);
    /* Allocate bit structures based on max prime */
    allocate_bits();
    init_bits();
    
    /* start the algorithm */
    sieve_of_eratosthenes();

    /* Output non marked numbers */
    print_primes();

    /* Deallocate bit structures */
    free_memory();
    free_threads();
    return EXIT_SUCCESS;
}
