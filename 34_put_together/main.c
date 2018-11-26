#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

char * getLines(char * line) {
  char * ptr = strchr(line, '\n');
  *ptr = '\0';
  return line;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file: %s", filename);
    return NULL;
  }

  counts_t * counts = createCounts();
  char * lines = NULL;
  size_t s = 0;
  while (getline(&lines, &s, f) >= 1) {
    char * key = getLines(lines);
    char * value = lookupValue(kvPairs, key);
    addCount(counts, value);
    free(lines);
    lines = NULL;
  }
  free(lines);

  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close file: %s", filename);
    return NULL;
  }
  
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Invalid no. of arguments!");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv_array = readKVs(argv[1]);
  if (kv_array == NULL) {
    fprintf(stderr, "Invalid file of Keys/Value Pairs!");
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv_array);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Cannot write to file: %s", outName);
      return EXIT_FAILURE;
    }
    
    //print the counts from c into the FILE f
    printCounts(c, f);
    
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close file: %s", outName);
      return EXIT_FAILURE;
    }
    
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv_array);
  
  return EXIT_SUCCESS;
}
