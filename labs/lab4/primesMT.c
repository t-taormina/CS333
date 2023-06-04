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

//t - user defined number of threads
//u - upper bound prime numbers that are displayed
//v - verbose
//h - help

extern unsigned short is_verbose;

int 
main( int argc, char *argv[] )
{
    process_cmd_line(argc, argv);
    check_verbose();
    return EXIT_SUCCESS;
}
