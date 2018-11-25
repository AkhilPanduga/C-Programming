#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int sortlines(FILE * f) {
  char ** lines = NULL;
  char * in = NULL;
  size_t s = 0;
  size_t len = 0;
  size_t j = 0;
  while((len = getline(&in, &s, f)) >= 0) {
    lines = realloc(lines, (j + 1) * sizeof(*lines));
    lines[j] = in;
    in = NULL;
    j++;
  }
  free(in);
  if (j == 0) {
    fprintf(stderr, "Invalid no. of Lines");
    for (size_t l = 0; l < j; l++)
      free(lines[l]);
    free(lines);
    return -1;
  }
  sortData(lines, j);
  for (size_t k = 0; k < j; k++) {
    printf("%s", lines[k]);
    free(lines[k]);
  }
  free(lines);
  return 0;
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  int result = 0;
  if (argc == 1) {
    FILE * f = stdin;
    if (f == NULL) {
	perror("Cannot open file");
	return EXIT_FAILURE;
      }
    result = sortlines(f);
    if (result < 0)
      return EXIT_FAILURE;
  }
  if (argc > 1) {
    for(size_t i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	perror("Cannot open file");
	return EXIT_FAILURE;
      }
      result = sortlines(f);
      if (result < 0)
	return EXIT_FAILURE;
      if (fclose(f) != 0) {
	perror("Failed to close the file");
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
