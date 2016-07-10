#ifndef HASH
#define HASH

typedef struct s_map_entry {
  char* key;
  void* value;
  struct s_map_entry *next;
} t_map_entry;

typedef struct s_map{
  t_map_entry** entries;
  int slots;
  int size;
  float load_factor;
  float grow_factor;
} t_map;


t_map* hashmap_create(int slots, float lf, float gf);
int hashmap_hashcode(char* key, int slots);
void hashmap_put(t_map* map, char* key, void* value);
void* hashmap_get(t_map* map, char* key);
void* hashmap_remove(t_map* map, char* key);
void hashmap_resize(t_map* map);
void* hashmap_delete(t_map* map, char* key);

/************* Ajout pour NoSQL *****************/

void* hashmap_traverse(t_hashmap*map, char* path) ; // Traverse a HashMap according to the given path
// Ex :  hashmap_traverse(map, 'student.rate')   14 ;
void hashmap_put(t_hashmap*map, char* path, void* value) ; // Traverse a HashMap according to the given path
// Ex :  hashmap_put(map, 'student.rate', 56);
//       hashmap_traverse(map, 'student.rate')   56

#endif
