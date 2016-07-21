#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

char* substring(char* str, unsigned from, unsigned to, char* substr){
  substr = malloc(sizeof(char)*(to-from+1));
  unsigned i;
  for(i = from; i < to; i++){
    substr[i-from] = str[i];
  }
  substr[i] = '\0';
  return substr;
}
