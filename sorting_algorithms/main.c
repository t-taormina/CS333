// Tyler Taormina
// taormina@pdx.edu

// Program that will take a flag indicating a sorting algorithm to
// be used and N amount of integers to be sorted. 
// Example: ~ ./sort -b 5 10 3 6 22 50 54
// Output: 3 5 6 10 22 50 54
// Four sorts: Bubble, Merge, Insertion, Tim-sort


#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int 
main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Needs argument provided on command line.\n");
  }

  unsigned long nums[argc - 1];
  int j = 0;
  for (int i = 1; i < argc; i++) {
    unsigned long n;
    n = strtol(argv[i], NULL, 10);
    nums[j] = n;
    j++;
  }

  unsigned long *nums_ptr = nums;
  bubble_sort(argc - 1, nums_ptr);

  exit(EXIT_SUCCESS);
}

