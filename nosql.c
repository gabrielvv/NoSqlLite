#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

#include "json.h"
#include "hashmap.h"
#include "nosql.h"
#include "utils.h"


void nosql_insert(char* collection, char* action_arg){
  //write a new object into file

  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection);
  fp = fopen(filename, "a");
  //write content
  fwrite(action_arg , 1 , sizeof(action_arg) , fp);
  fclose(fp);
}

void nosql_find(char* collection, char* action_arg){

  unsigned collection_size = get_count(collection);

  t_hashmap* to_find = JSON_parse(action_arg);

  char** keys = malloc(sizeof(char*)*to_find->size);
  int keys_len = hashmap_get_keys(to_find, keys);

  // printf("%s", to_find);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);

  load_collection(collection, map_array);

  unsigned i, j;
  unsigned count = 0;
  enum bool found = FALSE;

  for(i = 0; i < collection_size; i++){
    for(j = 0; j < keys_len; j++){
      if()
    }
  }

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

unsigned get_count(char* collection){

  FILE *fp;

  int ouvrante = 0; //123
  int fermante = 0; //125
  unsigned elements = 0;
  char c;
  unsigned i = 0;

  char filename[80];
  sprintf(filename, "%s.json", collection);
  fp = fopen(filename, "r");
  // il faut connaitre le nombre d'éléments de la collection pour malloc map_array => peut-être l'écrire dans la ligne numéro 1

  /****************** RECHERCHE TAILLE COLLECTION DANS HEADER ********************/

  char header[4];
  while((c = fgetc(fp)) && i < 4){
    header[i] = c;
    i++;
  }
  // printf("header %s", header);
  // printf("header to int %d", atoi(header));
  if(header[0] == 'H'){
    char* h = &(header[1]);
    return atoi(h);
  }
  /*********************************************************************************/

  i=0;
  rewind(fp);

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

  fclose(fp);
  return elements;
}

unsigned load_collection(char* collection, t_hashmap** map_array){

  FILE *fp;
  int ouvrante = 0; //123
  int fermante = 0; //125
  unsigned elements = 0;
  char c;
  unsigned i = 0;
  int start = -1;
  int end = -1;

  char filename[80];
  sprintf(filename, "%s.json", collection);
  fp = fopen(filename, "r");
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
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection_name);
  fp = fopen(filename, "w");
  //write content
  fwrite(collection_content , 1 , sizeof(collection_content) , fp );

  fclose(fp);
}

char* hashmap_array_to_string(t_hashmap** collection, int collection_size, char* collection_str){

  unsigned i;
  char** objects = malloc(sizeof(char*)*collection_size);
  unsigned total_size = 0; //la longueur totale de la string concaténant les objet
  int size_array[collection_size];

  for(i = 0; i < collection_size; i++){
    // objects[i] = JSON_stringify(collection[i]);
    size_array[i] = strlen(objects[i]);
    total_size += size_array[i]+1; // plus 1 pour le caractère de retour à la ligne entre chaque objet
  }

  collection_str = malloc(sizeof(char)*total_size);
  char* current_object;
  int current_size;
  unsigned j;

  for(i = 0; i < collection_size; i++){
    current_object = objects[i];
    current_size = size_array[i];
    for(j = 0; j < current_size; j++){
      collection_str[i+j] = current_object[j];
    }
    collection_str[i+j] = '\n';
  }
  return collection_str;
}
