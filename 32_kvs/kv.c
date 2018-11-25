#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * kvFromLines (char * lines) {
  kvpair_t * kv_pair = malloc(sizeof(*(kv_pair)));
  char * key = strsep(&lines, "=");
  char * value = strsep(&lines, "\n");

  kv_pair->key = strdup(key);
  kv_pair->value = strdup(value);

  return kv_pair;
}

void kvToArray (kvarray_t * kv_array, kvpair_t * kv_pair) {
  //kv_array->num_kv = kv_array->num_kv + 1;
  kv_array->kv = realloc(kv_array->kv, (kv_array->num_kv + 1) * sizeof(*(kv_pair)));
  kv_array->kv[(kv_array->num_kv)] = kv_pair;
  kv_array->num_kv++;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");

  if (f == NULL) {
    fprintf(stderr, "Cannot open file: %s", fname);
    return NULL;
  }

  kvarray_t * kv_array = malloc(sizeof(*(kv_array)));
  kv_array->kv = NULL;
  kv_array->num_kv = 0;
  char * lines = NULL;
  size_t s = 0;
  while (getline(&lines, &s, f) >= 1) {
    kvpair_t * kv_pair = kvFromLines(lines);
    kvToArray(kv_array, kv_pair);
    free(lines);
    lines = NULL;
  }
  free(lines);

  if (fclose(f) != 0) {
    fprintf(stderr,"Cannot close file: %s", fname);
    return NULL;
  }
  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->num_kv; i++) {
    free(pairs->kv[i]->key);
    free(pairs->kv[i]->value);
    free(pairs->kv[i]);
  }
  free(pairs->kv);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->num_kv; i++)
    printf("key = '%s' value = '%s'\n", pairs->kv[i]->key, pairs->kv[i]->value);
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->num_kv; i++) {
    if (strcmp(pairs->kv[i]->key, key) == 0)
      return pairs->kv[i]->value;
  }
  return NULL;
}
