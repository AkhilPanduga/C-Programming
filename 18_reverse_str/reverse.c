#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  int n = 0;
  for (int i = 0; str[i] != '\0'; i++)
    n++;
  char temp[n];
  if (n != 0) {
    str += (n - 1);
    for (int j = 0; j < n; j++) {
      temp[j] = *str;
      if (j < (n - 1))
	str--;
    }
    for (int k = 0; k < n; k++) {
      *str = temp [k];
      if (k < (n - 1))
	str++;
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
