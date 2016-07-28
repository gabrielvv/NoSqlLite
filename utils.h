#ifndef UTILS
#define UTILS

typedef enum bool bool;
enum bool {FALSE, TRUE};

typedef enum Writing_mode Writing_mode;
enum Writing_mode {WRITE, APPEND};

char* substring(char* str, unsigned from, unsigned to, char* substr);
void free_keys(char** k, int size);
void free_map_array(t_hashmap** map_array, unsigned size);

#endif
