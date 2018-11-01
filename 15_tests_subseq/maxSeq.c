
size_t maxSeq (int * array, size_t n) {
  if (n == 0)
    return 0;
  int seq[n] = { 0};
  for (size_t i = 0; i < n; i++) {
    seq[i] = *array;
    array++;
  }
  if (n == 1)
    return 1;
  int max[n] = { 0};
  int * max_p = &max;
  size_t x = 1;
  for (size_t j = 1; j < n; j++) {
    if (seq[j] > seq[j-1])
      x++;
    else {
      *max_p = x;
      max_p++;
      x = 1;
    }
  }
  int * seq_m = &max;
  for (size_t k = 1; k < n; k++) {
    if (*seq_m < max[k])
      seq_m = &max[k];
  }
  x = *seq_m;
  return x;
}
