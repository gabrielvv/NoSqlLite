#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include "json.h"
#include "hashmap.h"

// Convert a JSON String to a HashMap representation.
t_hashmap* JSON_parse(char* string){
  t_hashmap* map = malloc(sizeof(t_hashmap*));
  return map;
}

// Convert a HashMap to a JSON String representation.
char* JSON_stringify(t_hashmap* map){
  int x = 1;
  char* json = malloc(sizeof(char*)*x);
  return json;
}
