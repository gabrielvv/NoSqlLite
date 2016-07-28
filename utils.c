#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

char* substring(char* str, unsigned from, unsigned to, char* substr){
  unsigned i;
  for(i = from; i <= to; i++){
    substr[i-from] = str[i];
  }
  substr[i] = '\0';
  return substr;
}


void free_keys(char** k, int size){
  unsigned i;
  for(i = 0; i < size; i++){
    free(k[i]);
  }
}
