#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]) {
  char temp[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      temp[i][j] = matrix[i][j];
    }
  }
  for (int k = 0; k < 10; k++) {
    for (int l = 0; l < 10; l++) {
      matrix[k][l] = temp[9 - l][k];
    }
  }
}

int getmatrix(FILE * f) {
  char m[11];
  char matrix[10][10];
  int n = 0;
  int count = 0;
  while (fgets(m, 12, f) != NULL) {
    if (strchr(m, '\n') == NULL) {
      perror("Input colomuns do not form a 10x10 matrix");
      return EXIT_FAILURE;
    }  
    for (int l = 0; l < 12; l++) {
      if (m[l] == '\n')
	n = l;
    }
    if (n < 10) {
      perror("Input colomuns do not form a 10x10 matrix");
      return EXIT_FAILURE;
    }
    for (int j = 0; j < 10; j++)
      matrix[count][j] = m[j];
    count++;
  }
  if ((count < 10) || (count > 10)) {
    perror("Input rows do not form a 10x10 matrix");
    return EXIT_FAILURE;
  }
  rotate(matrix);
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < 10; k++) {
      printf("%c",matrix[i][k]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"No Input File\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error Opening File");
    return EXIT_FAILURE;
  }
  return getmatrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close input file");
    return EXIT_FAILURE;
  }
}
