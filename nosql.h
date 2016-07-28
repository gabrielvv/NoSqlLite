#ifndef NOSQL
#define NOSQL

void nosql_insert(char* collection, char* action_arg);
void nosql_find(char* collection, char* action_arg);
void nosql_find_sort(char* collection, char* action_arg, char* option_arg);
void nosql_find_projection(char* collection, char* action_arg, char* option_arg);
void nosql_remove(char* collection, char* action_arg);
void nosql_remove_where(char* collection, char* action_arg, char* option_arg);
void nosql_set(char* collection, char* action_arg);
void nosql_set_where(char* collection, char* action_arg, char* option_arg);

unsigned load_collection(char* collection, t_hashmap** map_array);
void write_collection(char* collection_name, char* collection_content);
unsigned get_count(char* collection);

#endif
