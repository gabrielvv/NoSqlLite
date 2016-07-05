#include "json.h"
#include <stdio.h> //printf
#include <stdlib.h> //malloc

t_hashmap* JSON_parse(char* string) ; // Convert a JSON String to a HashMap representation.
char* JSON_stringify(t_hashmap* map) ; // Convert a HashMap to a JSON String representation.
