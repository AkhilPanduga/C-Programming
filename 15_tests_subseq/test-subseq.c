#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main (void) {
  int array1[] = { };
  int array2[] = { 1};
  int array3[] = { -12, -9, -2, -1, 1, 4, 6, 7};
  int array4[] = { 1, 1, 2, 2, 3, 4, 5, 8};

  if (maxSeq(array1, 0) != 0) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array2, 1) != 1) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 8) != 5) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array3, 8) != 8) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
