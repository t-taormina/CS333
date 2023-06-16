// Tyler Taormina - taormina@pdx.edu

/*  gcc -g -Wall -o one 1.c -pthread  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <pthread.h>


int num_threads = 4;

void *rest(void *);


void *
rest(void * vid)
{
    int tid = (int) (vid);
    sleep(5);
    printf("thread id: %d resting...\n", tid); 
    pthread_exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv) 
{
    pthread_t *threads = NULL;
    long tid = 0;

    threads = malloc(num_threads * sizeof(pthread_t));

    for (tid = 0; tid < num_threads; tid++) {
        pthread_create(&threads[tid], NULL, rest, (void *) tid);
    }

    for (tid = 0; tid < num_threads; tid++) {
        pthread_join(threads[tid], NULL);
    }

    if (NULL != threads) {
        free(threads);
        threads = NULL;
    }




    return EXIT_SUCCESS;
}
