#include "hashmap.h"
#include <stdio.h> //printf
#include <stdlib.h> //malloc


void* hashmap_traverse(t_hashmap*map, char* path) ; // Traverse a HashMap according to the given path
// Ex :  hashmap_traverse(map, 'student.rate')   14 ;
void hashmap_put(t_hashmap*map, char* path, void* value) ; // Traverse a HashMap according to the given path
// Ex :  hashmap_put(map, 'student.rate', 56);
//       hashmap_traverse(map, 'student.rate')   56
