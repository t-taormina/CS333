/* Tyler Taormina - taormina@pdx.edu */
/* CS333 primesMT program - Lab 4 */

#include "sieveOE.h"

int 
main( int argc, char **argv)
{
    process_cmd_line(argc, argv);

    allocate_bits();

    init_bits();
    
    sieve_of_eratosthenes();

    print_primes();

    free_memory();

    return EXIT_SUCCESS;
}
