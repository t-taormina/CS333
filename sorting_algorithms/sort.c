// Tyler Taormina
// taormina@pdx.edu

#include "sort.h"

int 
bubble_sort(int argc, unsigned long *args) 
{
  if (argc <= 1)
    return 0;
  printf("Array: ");
  for (int i = 0; i < argc; i++) {
    printf("%ld ", args[i]);
  }


  args[0] = 4;
  args[1] = 5;
  args[2] = 6;

  printf("\n");
  return 1;
}



