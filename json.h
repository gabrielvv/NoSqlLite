#ifndef JSON
#define JSON

#include "hashmap.h"

typedef struct indexValue {
    int a;
    char* b;

}t_indexValue;


t_hashmap* JSON_parse(char* string) ; // Convert a JSON String to a HashMap representation.
char* JSON_stringify(t_hashmap* map) ; // Convert a HashMap to a JSON String representation.
t_indexValue* JSON_getKey(int index, char* json);
int getKeyValue(char* json);
void getKey(char* json,t_hashmap* map);
int jsonError(char * json);
char* removeSpace(char source[]);
char* removeQuote(char source[]);
char* printType(Type type);
int check_string( char* string);
void myStrcopy(char *copy, char* target, int size);
char* entryStringify(t_hashmap_entry* entry);
char* entryStringifySomeKeys(t_hashmap* map, char** keys, int size);
void JSON_stringify_project_and_print(t_hashmap* map, char** keys,int size);
void JSON_stringify_and_print(t_hashmap* map);
Type getType(char* value);

#endif
