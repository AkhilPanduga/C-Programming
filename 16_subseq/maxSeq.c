
unsigned maxSeq (int * array, unsigned n) {
  if (n == 0)
    return n;
  unsigned max = 1;
  unsigned l = 1;
  int seq[n];
  for (unsigned k = 0; k < n; k++) {
    seq[k] = 0;
  }
  unsigned array_l = sizeof(array)/sizeof(int);
  unsigned array_length = 1;
  if (array_l >= n){
    array_length = n;
  }
  else array_length = array_l;
  for (unsigned i = 0; i < array_length; i++) {
    seq[i] = *array;
    array++;
  }
  for (unsigned j = 1; j < n; j++) {
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
