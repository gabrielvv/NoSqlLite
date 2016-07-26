#include <stdio.h> //printf
#include <stdlib.h> //malloc

#include "json.h"
#include "hashmap.h"
#include "nosql.h"
#include "utils.h"


void nosql_insert(char* collection, char* action_arg){

}
void nosql_find(char* collection, char* action_arg){

}
void nosql_find_sort(char* collection, char* action_arg, char* option_arg){

}
void nosql_find_projection(char* collection, char* action_arg, char* option_arg){

}
void nosql__remove(char* collection, char* action_arg){

}
void nosql_remove_where(char* collection, char* action_arg, char* option_arg){

}
void nosql_set(char* collection, char* action_arg){

}
void nosql_set_where(char* collection, char* action_arg, char* option_arg){

}

int load_collection(char* collection, t_hashmap** map_array){

  FILE *fp;
  int ouvrante = 0; //123
  int fermante = 0; //125
  int elements = 0;
  char c;
  unsigned i = 0;
  int start = -1;
  int end = -1;

  fp = fopen(collection, "r");
  // il faut connaitre le nombre d'éléments de la collection pour malloc map_array => peut-être l'écrire dans la ligne numéro 1

 /**
  * 2 cas particuliers:
  *  - collection vide
  *  - collection mal formée
  */
  while((c = fgetc(fp)) != EOF){
    if(c == 123)
      ouvrante++;

    if(c == 125)
      fermante++;

    if(ouvrante == fermante && ouvrante != 0){
      elements++;
      ouvrante = 0;
      fermante = 0;
    }
    i++;
  }

  // collection mal formée -> on arrête tout
  if(ouvrante != 0 || fermante != 0)
    printf("\ncollection %s mal formee", collection);

  /********************* On charge tout le fichier dans une string ********************/
  
  int str_size = i; // i+1 est faux=>pourquoi?!
  // printf("str_size: %d", str_size);
  char str[str_size];
  rewind(fp);
  i=0;
  while((c = fgetc(fp)) != EOF){
    // printf("%c", c);
    str[i] = c;
    i++;
  }
  str[++i] = '\0'; //nécessaire ??

  /******************** on charge les données dans map_array ****************************/
  if(elements > 0){
    rewind(fp);

    map_array = malloc(sizeof(t_hashmap*)*elements);

    i = 0;
    while((c = fgetc(fp)) != EOF){
      if(c == 123){
        ouvrante++;
        if(start == -1)
          start = i;
      }
      if(c == 125)
        fermante++;

      if(ouvrante == fermante && ouvrante != 0){
        end = i;
        // printf("%d\n", end-start);
        char substr[end-start];

        // printf("str :\n%s\n", str);
        substring(str, start, end, substr);
        // printf("substr :\n%s\n", substr);

        /** TODO implémenter JSON_parse */
        // map_array[i] = JSON_parse(substr);
        ouvrante = 0;
        fermante = 0;
        start = -1;
      }
      i++;
    }//while

  }//elements > 0

  // if(elements == 0)
    // return map_array;

  fclose(fp);
  return elements;

}

void write_collection(char* collection_name, char* collection_content){
  // FILE *fp;
  // fp = fopen(collection, "w");
  //write content
  // fclose(fp);
}
