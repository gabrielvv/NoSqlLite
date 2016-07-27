#include <ctype.h>
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>
#include <string.h> // strlen

#include "json.h"
#include "hashmap.h"
#include "utils.h"

/**
* @see http://www.cplusplus.com/reference/cstring
* strchr  Locate first occurrence of character in string (function )
* strrchr Locate last occurrence of character in string (function )
* strcpy  Copy string
*/

// Convert a JSON String to a hasMap representation
t_hashmap* JSON_parse(char* string){
    //Volume p = DOUBLE;
    if(jsonError(string)==0){
        printf("Une erreur se trouve dans l'object json\n");
        return NULL;
    }
    // printf("%s",string);
    t_hashmap* map;
    if(string[0] == '{'){
        // printf("Début du parsing\n");
        map = hashmap_create(10,0.7, 2.2);
        //getKeyValue(string);
        char* json;
        const char delim[2] = ",";
        json = strtok (string,",");
       // char line[strlen(json)];

        //printf("Print de p %s\n",json);
        getKey(json,map);
        while (json!= NULL)
        {
            getKey(json,map);
            json = strtok (NULL, delim);
        }
    }
    return map;
}

void getKey(char* json,t_hashmap* map){
    char key[50] ="";
    char value[50] = "";
    int boolean = 0;
    Type type = STRING;
    if(type == STRING);
      printf("");

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
        else if((strcmp(valueSpace,"true")==0) || (strcmp(valueSpace,"false")==0)){
            type = BOOLEAN;
            break;
        }
        else if (check_string(valueSpace) == 1){
            type = INT;
            break;
        }
    }

    // printf("key :%s Value :%s ",keySpace,valueSpace);
    // printf(" Type :%s\n",printType(type));
    hashmap_put(map, keySpace, valueSpace);
    // printf("test getKey\n");

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

        case INT:
            return "INT";

        case DATE:
            return "DATE";
        default: return NULL;

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

// Convert a HashMap to a JSON String representation.
char* JSON_stringify(t_hashmap* map){
  /***********************************************
  - Faire un tableau de key-value
  - trouver les sous-objets et les convertir (en commençant par le niveau le plus bas de la hiérarchie -> récursivité)
  - convertir les key-value au niveau racine

  le caractère . indique un sous niveau dans la hiérarchie

  *************************************************/
  int x = 1;
  char* json = malloc(sizeof(char*)*x);
  return json;
}
