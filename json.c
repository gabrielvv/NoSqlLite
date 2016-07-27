#include <ctype.h>
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h> // strlen

#include "json.h"
#include "hashmap.h"



// Convert a JSON String to a hasMap representation
t_hashmap* JSON_parse(char* string){
    t_hashmap* map = malloc(sizeof(t_hashmap*));
    //Volume p = DOUBLE;
    if(jsonError(string)==0){
        printf("Une erreur se trouve dans l'object json\n");
        //return map;
    }
    printf("%s",string);
    if(string[0] == '{'){
        printf("Début du parsing\n");
        getKeyValue(string);
    }
    return map;
}

int getKeyValue(char* json){
    json = strtok (json,",");


    //printf("Print de p %s\n",p);
    getKey(json);

    while (json != NULL)
    {
        //printf ("%s\n",json);
        json = strtok (NULL, ",");
        getKey(json);
    }
    return 0;
}

void getKey(char* json){
    char key[50] ="";
    char value[50] = "";
    int boolean = 0;
    Type type;
    for (int i=0; i<strlen(json); i++){
        if(json[i] == '{' || json[i] == '}'){
            if(i == 0){
                json[i]=json[i+1];
                i++;
            }
            if(i == (strlen(json)-1)){
                json[i]= '\0';
                boolean = 1;
            }

        }
        if(json[i]==':') {
            boolean =1;
        }
        else{
            if(boolean ==0){
                size_t len = strlen(key);
                key[len++] = json[i];
                key[len] = '\0';
            }
            if(boolean == 1){
                size_t len = strlen(value);
                value[len++] = json[i];
                value[len] = '\0';
            }
        }


    }
    char* keySpace = removeSpace(key);
    char* valueSpace = removeSpace(value);
    //printf("key :%s\n",removeSpace(key));
   // printf("value :%s\n",removeSpace(value));

    int cpt=0;
    for(int i= 0; i<strlen(value);i++){
        if(valueSpace[i] == '\'' && (cpt%2)==0){
            type = STRING;
            //printf("Value Test quote%s\n",valueSpace);
            valueSpace = removeQuote(valueSpace);
            cpt ++;
            break;
        }
        else if((valueSpace == 'true') || (value == 'false')){
            type = BOOLEAN;
            break;
        }
        else if (check_string(valueSpace) == 1){
            type = DOUBLE;
            break;
        }
    }

    printf("key :%s Value :%s ",keySpace,valueSpace);
    printf(" Type :%s\n",printType(type));






}

int check_string( char* string) {
    const int string_len = strlen(string);
    for(int i = 0; i < string_len; ++i) {
        if(!isdigit(string[i]))
            return 0;
    }
    return 1;
}

char* printType(Type type){
    switch (type){
        case BOOLEAN:
            return "BOOLEAN";

        case STRING:
            return "String";

        case DOUBLE:
            return "DOUBLE";

        case DATE:
            return "DATE";

    }
}

char* removeQuote(char source[]){

    //char str[50] = "" ;
    char* str = malloc(50 * sizeof(char));

    int g= 0;
    for(int i=0;i<strlen(source);i++){
        if(i == 0){

        }else if(i == strlen(source)-1){
            str[g] = '\0';
        }else{
            str[g] = source[i];
            g++;
        }
    }
    return str;
}

char* removeSpace(char source[]){

    //char str[50] = "" ;
    char* str = malloc(50 * sizeof(char));

    int g= 0;
    for(int i=0;i<strlen(source);i++){
       if(source[i] != ' '){
           str[g]= source[i];
           g++;
       }
    }
    return str;
}

int jsonError(char * json){
    int jsonObjectBegin =0;
    int jsonObjectEnd = 0;
    int jsonArrayBegin = 0;
    int jsonArrayEnd = 0;
    for (int i=0; i<strlen(json); i++){
        if(json[i]=='{') jsonObjectBegin++;
        else if (json[i]=='}') jsonObjectEnd++;
        else if(json[i]=='[') jsonArrayBegin++;
        else if (json[i]==']') jsonArrayEnd++;
    }
    if( (jsonObjectBegin == jsonObjectEnd) && (jsonArrayBegin == jsonArrayEnd))
        return 1;
    else return 0;

}


// Convert a JSON String to a HashMap representation.
/*t_hashmap* JSON_parse(char* string){
=======

>>>>>>> e9505cfb13875bf570b2433daab7952ec753549e
  t_hashmap* map = malloc(sizeof(t_hashmap*));

  printf("Json à convertir : %s \n",string);
  printf("Longeur de la chaîne : %lu \n",strlen(string));
  int i=0;
  for (i=0; i<strlen(string);i++){
    switch (string[i]){
      case '{' :
        printf("Début du json\n");
            break;
      case '\'' :
        printf("Début d'une key\n");
            t_indexValue* jsonStructure = JSON_getKey(i,string);
            printf("index %d \n",jsonStructure->a);
            i = jsonStructure->a +1;
            break;

    }
  }
  return map;
}

 t_indexValue* JSON_getKey(int index, char* json){
  char key[50];
  int i=0;
  index++;
  printf("Affichage json first test %c\n",json[index]);
  for(int i=0; json[index]!='\'' ;i++){
    printf("%c \n",json[index]);
    key[i] = json[index];
    index++;
  }
   printf("key %s", key);
   t_indexValue* jsonStructure = malloc(sizeof(t_indexValue*));
   jsonStructure->a = index;
   jsonStructure->b = key;
   return jsonStructure;


}*/



// Convert a HashMap to a JSON String representation.
char* JSON_stringify(t_hashmap* map){
  int x = 1;
  char* json = malloc(sizeof(char*)*x);
  return json;
}
