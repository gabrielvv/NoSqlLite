#ifndef UTILS
#define UTILS

typedef enum bool bool;
enum bool {FALSE, TRUE};

typedef enum Writing_mode Writing_mode;
enum Writing_mode {WRITE, APPEND};

char* substring(char* str, unsigned from, unsigned to, char* substr);
void** quick_sort(void** list, int len);
int generic_cmp(void* a, void* b);


#endif
