#ifndef JSON
#define JSON

#include "hashmap.h"


t_hashmap* JSON_parse(char* string) ; // Convert a JSON String to a HashMap representation.
t_hashmap* JSON_parse_sub(char* root, char* string, t_hashmap* map);
char* JSON_stringify(t_hashmap* map) ; // Convert a HashMap to a JSON String representation.

#endif
