#ifndef JSON
#define JSON

#include "hashmap.h"


t_hashmap* JSON_parse(char* string, t_hashmap* map) ; // Convert a JSON String to a HashMap representation.
char* JSON_stringify(t_hashmap* map) ; // Convert a HashMap to a JSON String representation.

#endif
