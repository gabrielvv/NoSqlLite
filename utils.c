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

void** quick_sort(void** list, int len){
  if(len < 2)
    return;

  void* pivot = list[0];
  list = &list[1];
}

int generic_cmp(void* a, void* b){
  printf("%d")
}
