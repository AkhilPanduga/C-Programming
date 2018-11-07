#include <stdlib.h>

unsigned mult(unsigned x, unsigned y, unsigned ans) {
  if(y == 0) {
    return ans;
  }
  else if(y > 0) {
    return mult(x, y-1, x * ans);
  }
  exit(EXIT_FAILURE);
}

unsigned power(unsigned x, unsigned y) {
  return mult(x, y, 1);
}
