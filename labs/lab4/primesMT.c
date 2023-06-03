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
//#include <sys/param.h>


//#include ".h"


// I have this a global so that I don't have to pass it to every
// function where I might want to use it. Yes, I know global variables
// are frowned upon, but there are a couple of times where they can use
// their power for good. This is one.
extern unsigned short is_verbose;

int 
main( int argc, char *argv[] )
{
    printf("hello, world!\n");
    return EXIT_SUCCESS;
}
