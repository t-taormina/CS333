// Tyler Taormina
// taormina@pdx.edu

#include "sort.h"

int 
bubble_sort(int argc, unsigned long *args) 
{
  if (argc <= 1)
    return 2;

  // Sort here
  
  printf("Array: ");
  for (int i = 0; i < argc; i++) {
    printf("%ld ", args[i]);
  }
  return 0;
}

int 
merge_sort(int argc, unsigned long *args) 
{
  if (argc <= 1)
    return 2;

  // Sort here

  printf("Array: ");
  for (int i = 0; i < argc; i++) {
    printf("%ld ", args[i]);
  }
  return 0;
}

int 
insertion_sort(int argc, unsigned long *args) 
{
  if (argc <= 1)
    return 2;

  // Sort here

  printf("Array: ");
  for (int i = 0; i < argc; i++) {
    printf("%ld ", args[i]);
  }
  return 0;
}

int 
tim_sort(int argc, unsigned long *args) 
{
  if (argc <= 1)
    return 2;

  // Sort here

  printf("Array: ");
  for (int i = 0; i < argc; i++) {
    printf("%ld ", args[i]);
  }
  return 0;
}

