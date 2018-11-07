
#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("Invalid answer as power(%d, %d) is not equal to %d\n", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(-1, 0, 1);
  run_check(10, 5, 100000);
  printf("Tests Passed\n");
  return EXIT_SUCCESS;
}
