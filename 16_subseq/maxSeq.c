
unsigned maxSeq (int * array, unsigned n) {
  if (n == 0)
    return n;
  unsigned max = 1;
  unsigned l = 1;
  int seq[n] = {0};
  for (unsigned i = 0; i < n; i++) {
    seq[i] = *array;
    array++;
  }
  for (unsigned j = 1; j <= n; i++) {
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
