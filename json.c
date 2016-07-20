#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h> // strlen

#include "json.h"
#include "hashmap.h"



// Convert a JSON String to a HashMap representation.
t_hashmap* JSON_parse(char* string){
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


}



// Convert a HashMap to a JSON String representation.
char* JSON_stringify(t_hashmap* map){
  int x = 1;
  char* json = malloc(sizeof(char*)*x);
  return json;
}
