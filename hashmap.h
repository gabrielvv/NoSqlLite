#ifndef HASH
#define HASH

typedef struct s_hashmap_entry {
  char* key;
  void* value;
  struct s_hashmap_entry *next;
} t_hashmap_entry;

typedef struct s_hashmap{
  t_hashmap_entry** entries;
  int slots;
  int size;
  float load_factor;
  float grow_factor;
} t_hashmap;


t_hashmap* hashmap_create(int slots, float lf, float gf);
int hashmap_hashcode(char* key, int slots);
void hashmap_put(t_hashmap* map, char* path, void* value);
void* hashmap_get(t_hashmap* map, char* path);
void* hashmap_remove(t_hashmap* map, char* key);
void hashmap_resize(t_hashmap* map);
void* hashmap_delete(t_hashmap* map, char* key);
int hashmap_free(t_hashmap* map);

#endif
