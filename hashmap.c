#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

#include "hashmap.h"

// OK
t_hashmap* hashmap_create(int slots, float lf, float gf){

  t_hashmap* map = malloc(sizeof(t_hashmap));

  map->entries = malloc(sizeof(t_hashmap_entry*)*slots);
  int i;
  for(i = 0; i < slots; i++){
    map->entries[i] = NULL;
  }
  map->slots = slots;
  map->size = 0;
  map->load_factor = lf;
  map->grow_factor = gf;

  return map;
}

// OK
t_hashmap_entry* hashmap_entry_create(char* k, void* v){
  t_hashmap_entry* entry = malloc(sizeof(t_hashmap_entry));
  entry->key = k;
  entry->value = v;
  entry->next = NULL;
  return entry;
}

// OK
int hashmap_hashcode(char* key, int slots) {
  int hash = 0;
  int i;
  for (i = 0 ; key[i] != '\0' ; i++) {
    hash = 31*hash + key[i];
  }
  return hash % slots;
}

// NON OK
// Ex :  hashmap_put(map, 'student.rate', 56);
//       hashmap_traverse(map, 'student.rate')   56
void hashmap_put(t_hashmap* map, char* path, void* value) {

  printf("\n---------------MAP_PUT-------------------");
  printf("\nmap->size: %d\tmap->slots*load_factor: %f\tpath: %s\tvalue: %s", map->size, map->slots * map->load_factor, path, (char*)value);
  if(map->size >= (map->slots * map->load_factor)){
    hashmap_resize(map);

    printf("\nafter resize map->slots: %d\tmap->size: %d", map->slots, map->size);
  }

  int slot = hashmap_hashcode(path, map->slots);
  t_hashmap_entry** entries = &(map->entries[slot]);

  while ((*entries) != NULL) {
    if (strcmp((*entries)->key, path) == 0) {
      (*entries)->value = value;
      return;
    }
    entries = &((*entries)->next);
  }

  (*entries) = hashmap_entry_create(path, value);
  map->size++;
}

// NON OK
void hashmap_resize(t_hashmap* map){

  printf("\n---------------MAP_RESIZE-------------------");
  map->slots = map->slots * map->grow_factor;
  t_hashmap_entry** entries = map->entries;
  map->entries = malloc(sizeof(t_hashmap_entry*)*map->slots);
  map->size = 0;
  int i;
  for(i = 0; i < map->slots; i++){
    t_hashmap_entry* entry = entries[i];
    while(entry !=  NULL){
      hashmap_put(map, entry->key, entry->value);
      entry = entry->next;
    }
    printf("\nfin while");
  }
}

// OK
void* hashmap_get(t_hashmap* map, char* path) {
  int slot = hashmap_hashcode(path, map->slots);
  t_hashmap_entry* entries = map->entries[slot];

  while (strcmp(entries->key,path) != 0 && entries != NULL)  {
    entries = entries->next;
  }
  return strcmp(entries->key,path) != 0 ? NULL : entries->value;
}


// OK
void* hashmap_remove(t_hashmap* map, char* key){

  int mKey = hashmap_hashcode(key, map->slots);
  t_hashmap_entry* current_entry = map->entries[mKey];

  t_hashmap_entry* previous_entry = NULL;

  while(strcmp(current_entry->key, key) != 0 && current_entry->next != NULL){
    // printf("\nwhile");
    previous_entry = current_entry;
    current_entry = current_entry->next;
  }

  if(strcmp(current_entry->key, key) != 0)
    return NULL;

  char* value = current_entry->value;

  //le maillon est le premier de la chaîne
  if(!previous_entry){
    //printf("\nle maillon est le premier de la chaine");
    map->entries[mKey % (map->slots)] = current_entry->next;
  }

  //le maillon est au milieu de la chaine
  if(previous_entry && current_entry->next){
    // printf("\nle maillon est au milieu de la chaine");
    previous_entry->next = current_entry->next;
  }

  //sinon: le maillon est en fin de chaine
  free(current_entry);
  map->size--;

  return value;
}

// OK
void* hashmap_delete(t_hashmap* map, char* key){
  int slot = hashmap_hashcode(key, map->slots);
  void* value = NULL;
  t_hashmap_entry **entry = &(map->entries[slot]), *toDelete;
  while(*entry){
    if(strcmp((*entry)->key, key) == 0){
      value = (*entry)->value;
      toDelete = *entry;
      *entry = (*entry)->next;
      free(toDelete);
      return value;
    }
    *entry = (*entry)->next;
  }
  return value;
}
