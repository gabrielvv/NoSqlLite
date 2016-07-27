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

 /**
  * Transforme l'argument en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_find = JSON_parse(action_arg);
  char** keys = malloc(sizeof(char*)*to_find->size);
  int keys_len = hashmap_get_keys(to_find, keys);

 /**
  * Tableau de hashmaps représentant les objets stockés
  * dans le fichier
  */
  unsigned collection_size = get_count(collection);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);
  load_collection(collection, map_array);

  unsigned i, j;
  bool found = (to_find->size == 0 ? TRUE : FALSE);

 /**
  * Iteration dans le tableau de hashmap
  * Quand une hashmap satisfait aux conditions
  * définies par les arguments,
  * on l'affiche
  */
  for(i = 0; i < collection_size; i++){
    t_hashmap* map = map_array[i];

    for(j = 0; j < keys_len; j++){
      char* key = keys[j];
      if(strcmp( hashmap_get(to_find, key), hashmap_get(map, key) ) == 0){
        found = TRUE;
      }else{
        found = FALSE;
        break;
      }
    }

    if(found == TRUE)
      JSON_stringify_and_print(map);

    hashmap_free(map)
  }//for
}

void nosql_find_sort(char* collection, char* action_arg, char* option_arg){

}

void nosql_find_projection(char* collection, char* action_arg, char* option_arg){
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_find = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_find->size);
  int action_keys_len = hashmap_get_keys(to_find, action_keys);

  /**
  * Transforme l'argument option en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_project = JSON_parse(action_arg);
  char** option_keys = malloc(sizeof(char*)*to_project->size);
  int option_keys_len = hashmap_get_keys(to_project, option_keys);

  /**
  * Tableau de hashmaps représentant les objets stockés
  * dans le fichier
  */
  unsigned collection_size = get_count(collection);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);
  load_collection(collection, map_array);

  unsigned i, j;
  bool found = (to_find->size == 0 ? TRUE : FALSE);

  /**
  * Iteration dans le tableau de hashmap
  * Quand une hashmap satisfait aux conditions
  * définies par les arguments,
  * on l'affiche
  */
  for(i = 0; i < collection_size; i++){
    t_hashmap* map = map_array[i];

    for(j = 0; j < action_keys_len; j++){
      char* key = action_keys[j];
      if(strcmp( hashmap_get(to_find, key), hashmap_get(map, key) ) == 0){
        found = TRUE;
      }else{
        found = FALSE;
        break;
      }
    }

    if(found == TRUE)
      JSON_stringify_project_and_print(map, option_keys);

    hashmap_free(map);
  }//for
}

void nosql_remove(char* collection, char* action_arg){
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_find = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_find->size);
  int action_keys_len = hashmap_get_keys(to_find, action_keys);

  /**
  * Tableau de hashmaps représentant les objets stockés
  * dans le fichier
  */
  unsigned collection_size = get_count(collection);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);
  load_collection(collection, map_array);

  unsigned i, j;
  bool found = (to_find->size == 0 ? TRUE : FALSE);
  for(i = 0; i < collection_size; i++){
   t_hashmap* map = map_array[i];

    for(j = 0; j < action_keys_len; j++){
      char* key = action_keys[j];
      if(strcmp( hashmap_get(to_find, key), hashmap_get(map, key) ) == 0){
        found = TRUE;
      }else{
        found = FALSE;
        break;
      }
    }
    if(found == TRUE)
      hashmap_put(map, key, hashmap_get(to_set, key));

    if(i == 0){
      fp = fopen(filename,"w");
      char[] collection_content = JSON_stringify(map);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }else{
      fp = fopen(filename,"a");
      char[] collection_content = JSON_stringify(map);
      fwrite("\n", 1, sizeof("\n"), fp);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }
  }//for

  hashmap_free(map);
}

void nosql_set(char* collection, char* action_arg){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection_name);
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_set = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_find->size);
  int action_keys_len = hashmap_get_keys(to_find, action_keys);

  /**
  * Tableau de hashmaps représentant les objets stockés
  * dans le fichier
  */
  unsigned collection_size = get_count(collection);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);
  load_collection(collection, map_array);

 /**
  * Iteration dans le tableau de hashmap
  * Quand une hashmap satisfait aux conditions
  * définies par les arguments,
  * on l'affiche
  */
  unsigned i, j;
  for(i = 0; i < collection_size; i++){
    t_hashmap* map = map_array[i];

    for(j = 0; j < action_keys_len; j++){
      hashmap_put(map, key, hashmap_get(to_set, key));
    }
    if(i == 0){
      fp = fopen(filename,"w");
      char[] collection_content = JSON_stringify(map);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }else{
      fp = fopen(filename,"a");
      char[] collection_content = JSON_stringify(map);
      fwrite("\n", 1, sizeof("\n"), fp);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }
  }//for

  // char* collection_str = hashmap_array_to_string(t_hashmap** map_array, collection_size);
  hashmap_free(map);
}

void nosql_set_where(char* collection, char* action_arg, char* option_arg){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection_name);
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_set = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_find->size);
  int action_keys_len = hashmap_get_keys(to_find, action_keys);

  /**
  * Transforme l'argument option en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_project = JSON_parse(action_arg);
  char** option_keys = malloc(sizeof(char*)*to_project->size);
  int option_keys_len = hashmap_get_keys(to_project, option_keys);

  /**
  * Tableau de hashmaps représentant les objets stockés
  * dans le fichier
  */
  unsigned collection_size = get_count(collection);
  t_hashmap** map_array = malloc(sizeof(t_hashmap*)*collection_size);
  load_collection(collection, map_array);

 /**
  * Iteration dans le tableau de hashmap
  * Quand une hashmap satisfait aux conditions
  * définies par les arguments,
  * on l'affiche
  */
  unsigned i, j;
  int count = 0;
  bool found = (to_find->size == 0 ? TRUE : FALSE);
  for(i = 0; i < collection_size; i++){
    t_hashmap* map = map_array[i];

    for(j = 0; j < action_keys_len; j++){
      char* key = action_keys[j];
      if(strcmp( hashmap_get(to_find, key), hashmap_get(map, key) ) == 0){
        found = TRUE;
      }else{
        found = FALSE;
        break;
      }
    }

    if(found == FALSE){
      if(count == 0){
        fp = fopen(filename,"w");
        char[] collection_content = JSON_stringify(map);
        fwrite(collection_content, 1 , sizeof(collection_content) , fp);
        fclose(fp);
      }else{
        fp = fopen(filename,"a");
        char[] collection_content = JSON_stringify(map);
        fwrite("\n", 1, sizeof("\n"), fp);
        fwrite(collection_content, 1 , sizeof(collection_content) , fp);
        fclose(fp);
      }
      count++;
    }
  }//for
  hashmap_free(map);
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

        map_array[i] = JSON_parse(substr);
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

void write_collection(char* collection_name, char* collection_content, Writing_mode mode){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection_name);
  fp = fopen(filename, mode == WRITE ? "w" : "a");
  //write content
  fwrite(collection_content , 1 , sizeof(collection_content) , fp);
  fclose(fp);
}

char* hashmap_array_to_string(t_hashmap** collection, int collection_size){

  unsigned i;
  char* collection_str;
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
