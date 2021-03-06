
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

void decrypt (FILE * f) {
  int c;
  int freq[26] = {0};
  int key;
  while ((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      freq[c - 97] += 1;
    }
  }
  int max = maxfreq(freq);
  if (max >= 4)
    key = max - 4;
  if (max < 4)
    key = max + 22;
  if (key >= 0 && key < 26)
    printf("%d\n", key);
  else fprintf(stderr, "Decyption Failed");
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Enter Input File\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error Opening File");
    return EXIT_FAILURE;
  }
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
