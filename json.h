#ifndef JSON
#define JSON

#include "hashmap.h"

typedef enum Type Type;
enum Type
{
    INT,BOOLEAN, STRING,FLOAT,DATE
};

typedef struct indexValue {
    int a;
    char* b;

}t_indexValue;


t_hashmap* JSON_parse(char* string, t_hashmap* map) ; // Convert a JSON String to a HashMap representation.
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

#endif
