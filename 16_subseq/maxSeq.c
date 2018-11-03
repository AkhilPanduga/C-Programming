
int maxSeq (int * array, int n) {
  if (n == 0)
    return n;
  int  max = 1;
  int l = 1;
  int seq[n];
  for (int k = 0; k < n; k++) {
    seq[k] = 0;
  }
  for (int i = 0; i < n; i++) {
    seq[i] = *array;
    array++;
  }
  for (int j = 1; j < n; j++) {
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
