#ifndef JSON
#define JSON

#include "hashmap.h"

typedef enum Type Type;
enum Type
{
    DOUBLE,BOOLEAN, STRING,DATE
};

typedef struct indexValue {
    int a;
    char* b;
    Type type;

}t_indexValue;


t_hashmap* JSON_parse(char* string) ; // Convert a JSON String to a HashMap representation.
char* JSON_stringify(t_hashmap* map) ; // Convert a HashMap to a JSON String representation.
t_indexValue* JSON_getKey(int index, char* json);
 int getKeyValue(int index, char* json);
void getKey(char* json);
int jsonError(char * json);
char* removeSpace(char source[]);
char* removeQuote(char source[]);
char* printType(Type type);

#endif
