
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int maxfreq (int * arr) {
  int maxf = 0;
  for (int i = 0; i < 26; i++) {
    if (arr[i] > arr[maxf])
      maxf = i;
  }
  return maxf;
}

void decrypt (FILE * g, int n) {
  int c;
  int i = 0;
  int ch[n];
  while ((c = fgetc(g)) != EOF) {
    if(isalpha(c)) {
      ch[i] = tolower(c);
      i++;
    }
  }
  int freq[26] = {0};
  int key;
  for (int j = 0; j < n; j++)
    freq[ch[j] - 97] += 1;
  int max = maxfreq(freq);
  if (max >= 4)
    key = max - 4;
  else key = max + 22;
  if (key < 0 || key >= 26)
    fprintf(stderr, "Decyption Failed");
  else printf("%d\\n", key);
}

int lettercount (FILE * f) {
  int c;
  int l = 0;
  while ((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      l++;
    }
  }
  return l;
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Enter Input File\n");
    return EXIT_FAILURE;
  }
  int n = 0;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error Opening File");
    return EXIT_FAILURE;
  }
  n = lettercount(f);
  fclose(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
  FILE * g = fopen(argv[1], "r");
  decrypt(g, n);
  fclose(g);
  if (fclose(g) != 0) {
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
