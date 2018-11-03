#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t i, size_t n);

int main (void) {
  int array1[] = { 1};
  int array2[] = { 1};
  int array3[] = { -12, -9, -2, -1, 1, 4, 6, 7};
  int array4[] = { 1, 1, 2, 2, 3, 4, 5, 8};

  if (maxSeq(array1, 1, 0) != 0) {
    printf("no at 1");
    return EXIT_FAILURE;
  }
  if (maxSeq(array2, 1, 1) != 1) {
    printf("no at 2");
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 8, 8) != 5) {
    printf("no at 3");
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 8, 10) != 5) {
    printf("no at 4");
    return EXIT_FAILURE;
  }
  if (maxSeq(array3, 8, 8) != 8) {
    printf("no at 5");
    return EXIT_FAILURE;
  }
  printf("YES\n");
  return EXIT_SUCCESS;
}
