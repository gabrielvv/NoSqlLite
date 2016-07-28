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
  printf("action_arg %s\t sizeof: %d\n", action_arg, strlen(action_arg));
  fwrite(action_arg , 1 , strlen(action_arg) , fp);
  fwrite("\n" , 1 , 1 , fp);
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
  printf("%s\n", hashmap_get(map_array[0], "name"));
  printf("%s\n",  hashmap_get(map_array[0], "rate"));
  printf("%s\n", hashmap_get(map_array[0], "group"));
  printf("%s\n", hashmap_get(map_array[1], "name"));
  printf("%s\n",  hashmap_get(map_array[1], "rate"));
  printf("%s\n", hashmap_get(map_array[1], "group"));
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

    //TRY MATCHING OBJECT IF FIND OBJECT NOT EMPTY
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
  }//for

  free_keys(keys, to_find->size);
  hashmap_free(to_find);
  free_map_array(map_array, collection_size);

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
      JSON_stringify_project_and_print(map, option_keys, option_keys_len);
  }//for

  free_keys(action_keys, to_find->size);
  free_keys(option_keys, to_project->size);
  hashmap_free(to_find);
  hashmap_free(to_project);
  free_map_array(map_array, collection_size);
}

/****************** REMOVE **************************/

void nosql_remove(char* collection, char* action_arg){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection);
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
    } //for

    if(found == FALSE){
      if(count == 0){
        fp = fopen(filename,"w");
        char* collection_content = JSON_stringify(map);
        fwrite(collection_content, 1 , sizeof(collection_content) , fp);
        fclose(fp);
      }else{
        fp = fopen(filename,"a");
        char* collection_content = JSON_stringify(map);
        fwrite("\n", 1, sizeof("\n"), fp);
        fwrite(collection_content, 1 , sizeof(collection_content) , fp);
        fclose(fp);
      }
      count++;
    }//if

  }//for

  free_keys(action_keys, to_find->size);
  hashmap_free(to_find);
  free_map_array(map_array, collection_size);
}

/************************** SET **************************/

void nosql_set(char* collection, char* action_arg){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection);
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_set = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_set->size);
  int action_keys_len = hashmap_get_keys(to_set, action_keys);

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
    //SET NEW VALUES
    for(j = 0; j < action_keys_len; j++){
      char* key = action_keys[j];
      void* value = hashmap_get(to_set, key);
      hashmap_put(map, key, value, getType(value));
    }
    //WRITE
    if(i == 0){
      fp = fopen(filename,"w");
      char* collection_content = JSON_stringify(map);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }else{
      fp = fopen(filename,"a");
      char* collection_content = JSON_stringify(map);
      fwrite("\n", 1, sizeof("\n"), fp);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }
  }//for


  free_keys(action_keys, to_set->size);
  hashmap_free(to_set);
  free_map_array(map_array, collection_size);
}

/****************  SET WHERE ********************/

void nosql_set_where(char* collection, char* action_arg, char* option_arg){
  FILE *fp;
  char filename[80];
  sprintf(filename, "%s.json", collection);
  /**
  * Transforme l'argument action en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* to_set = JSON_parse(action_arg);
  char** action_keys = malloc(sizeof(char*)*to_set->size);
  int action_keys_len = hashmap_get_keys(to_set, action_keys);

  /**
  * Transforme l'argument option en hashmap
  * Remplie un tableau avec les valeurs des clés de l'argument
  *
  */
  t_hashmap* where = JSON_parse(action_arg);
  char** option_keys = malloc(sizeof(char*)*where->size);
  // int option_keys_len = hashmap_get_keys(where, option_keys);

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
  char* key;
  bool found = (to_set->size == 0 ? TRUE : FALSE);
  for(i = 0; i < collection_size; i++){
    t_hashmap* map = map_array[i];
    //FIND MATCHING OBJECT
    for(j = 0; j < action_keys_len; j++){
      key = option_keys[j];
      if(strcmp( hashmap_get(where, key), hashmap_get(map, key) ) == 0){
        found = TRUE;
      }else{
        found = FALSE;
        break;
      }
    }
    //SET NEW VALUES WHEN OBJECT MATCH FILTER
    if(found == TRUE){
      for(j = 0; j < action_keys_len; j++){
        key = action_keys[j];
        void* value = hashmap_get(to_set, key);
        hashmap_put(map, key, value, getType(value));
      }
    }

    if(i == 0){
      fp = fopen(filename,"w");
      char* collection_content = JSON_stringify(map);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }else{
      fp = fopen(filename,"a");
      char* collection_content = JSON_stringify(map);
      fwrite("\n", 1, sizeof("\n"), fp);
      fwrite(collection_content, 1 , sizeof(collection_content) , fp);
      fclose(fp);
    }//if

  }//for

  free_keys(action_keys, to_set->size);
  free_keys(option_keys, where->size);
  hashmap_free(to_set);
  hashmap_free(where);
  free_map_array(map_array, collection_size);

}

/********************  GET COUNT ******************/

/**
* @desc
* Count how many objects are stored in collection
* Try to read the header to get the count
* If it does not find the header, it reads and analyze the whole file
*
* @param collection : the collection name
*
* @return count : number of objects stored in collection
*/
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
  str[i-1] = '\0'; //nécessaire ??

  /******************** on charge les données dans map_array ****************************/
  int cpt = 0;
  if(elements > 0){

    rewind(fp);
    // map_array = malloc(sizeof(t_hashmap*)*elements);
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
        memset(substr,0,strlen(substr));
        // printf("str :%s\n", str);
        substring(str, start, end, substr);
        printf("substr :%s\n", substr);

        map_array[cpt] = JSON_parse(substr);
        // printf("map index %d :%p\n",cpt, map_array[cpt]);
        ouvrante = 0;
        fermante = 0;
        start = -1;
        cpt++;
      }
      i++;
    }//while

  }//elements > 0

  // if(elements == 0)
    // return map_array;
  fclose(fp);
  return elements;
}
