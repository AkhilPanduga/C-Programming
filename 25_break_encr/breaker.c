
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int maxfreq (int * arr) {
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (arr[i] > arr[max])
      max = i;
  }
  return max;
}

void decrypt (int * arr) {
  int freq[26] = {0};
  int key;
  for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
    freq[arr[i] - 97] += 1;
  int max = maxfreq(freq);
  if (max >= 4)
    key = max - 4;
  else key = max + 22;
  if (key < 0 || key >= 26)
    fprintf(stderr, "Decyption Failed");
  else printf("%d\\n", key);
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Enter Input File\n");
    return EXIT_FAILURE;
  }
  int c;
  int n = 0;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error Opening File");
    return EXIT_FAILURE;
  }
  int i = 0;
  int ch[10000];
  while ((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      ch[n] = tolower(c);
      n++;
    }
  }
  decrypt(ch);
  if (fclose(f) != 0) {
    perror("Failed to close the input file");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
