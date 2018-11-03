
size_t maxSeq (int * array, size_t n) {
  if (n == 0)
    return n;
  size_t max = 1;
  size_t l = 1;
  int seq[n];
  for (size_t k = 0; k <= n; k++) {
    seq[k] = 0;
  }
  for (size_t i = 0; i < n; i++) {
    seq[i] = *array;
    array++;
  }
  for (size_t j = 1; j <= n; j++) {
    if (seq[j] > seq[j-1])
      l++;
    else
      if (max < l) {
	max = l;
	l = 1;
      }
    if (max < l)
      max = l;
  }
  return max;
}
