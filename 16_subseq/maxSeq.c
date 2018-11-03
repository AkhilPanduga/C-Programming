
unsigned maxSeq (int * array, unsigned i, unsigned n) {
  if ((n == 0) || (i == 0))
    return n;
  unsigned max = 1;
  unsigned l = 1;
  int seq[n];
  for (unsigned k = 0; k < n; k++) {
    seq[k] = 0;
  }
  for (unsigned m = 0; m < i; m++) {
    seq[m] = *array;
    array++;
  }
  for (unsigned j = 1; j < n; j++) {
    if (seq[j] > seq[j-1])
      l++;
    else {
      if (max < l) {
	max = l;
	l = 1;
      }
      else {
	l = 1;
      }
    }
    if (max < l)
      max = l;
  }
  return max;
}
