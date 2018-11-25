#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->arrayCount = malloc(sizeof(counts->arrayCount));
  counts->arrayLen = 0;
  counts->unLen = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL)
    c->unLen++;
  else {
    int a = 0;
    int c_array = 0;
    for (int i = 0; i < c->arrayLen; i++) {
      if (strcmp(c->arrayCount[i]->str, name) == 0) {
	//cannot use c_array++ to properly increment nStrCount
	c_array = 1;
	break;
      }
      a++;
    }
    if (c_array == 1)
      c->arrayCount[a]->nStrCount++;
    else {
      c->arrayCount = realloc(c->arrayCount, (c->arrayLen + 1) * sizeof(*(c->arrayCount)));
      c->arrayCount[c->arrayLen] = malloc(sizeof(one_count_t));
      c->arrayCount[c->arrayLen]->str = name;
      c->arrayCount[c->arrayLen]->nStrCount = 1;
      c->arrayLen++;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (c->unLen >= 1)
    fprintf(outFile, "<unknown>: %d\n", c->unLen);
  for (int i = 0; i < c->arrayLen; i++)
    fprintf(outFile, "%s: %d\n", c->arrayCount[i]->str, c->arrayCount[i]->nStrCount);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->arrayLen; i++)
    free(c->arrayCount[i]);
  free(c->arrayCount);
  free(c);
}
