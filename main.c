#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hashmap.h"
#include "JSON.h"
#include "cli.h"
#include "nosql.h"

void test_hashmap_put();
void test_hashmap_get();
void test_json();

int main(){
  // test_json();
  test_hashmap_put();
  test_hashmap_get();
  return 0;
}

// OK
void test_hashmap_put(){

  int slots = 10;
  t_hashmap* map = hashmap_create(slots, 0.7, 2.2);
  int hash[10];
  hash[0] = hashmap_hashcode("foo", slots);
  hash[1] = hashmap_hashcode("bar", slots);
  hash[2] = hashmap_hashcode("baz", slots);
  hash[3] = hashmap_hashcode("luz", slots);
  hash[4] = hashmap_hashcode("lol", slots);
  hash[5] = hashmap_hashcode("aaa", slots);
  hashmap_put(map, "foo", "foo");
  hashmap_put(map, "bar", "bar");
  hashmap_put(map, "baz", "baz");
  hashmap_put(map, "luz", "luz");
  hashmap_put(map, "lol", "lol");
  hashmap_put(map, "aaa", "aaa");
  printf("\n----------------------------TEST: HASHMAP_PUT WITHOUT RESIZE---------------\n");
  char* value = (char*) map->entries[hash[0]]->value;
  printf("hash: %d\t value: %s\t %s\n", hash[0], value, strcmp(value, "foo") == 0? "PASS" : "FAIL");
  value = (char*) map->entries[hash[1]]->value;
  printf("hash: %d\t value: %s\t %s\n", hash[1], value, strcmp(value, "bar") == 0? "PASS" : "FAIL");
  value = (char*) map->entries[hash[2]]->value;
  printf("hash: %d\t value: %s\t %s\n", hash[2], value, strcmp(value, "baz") == 0? "PASS" : "FAIL");
  value = (char*) map->entries[hash[3]]->next->value;
  printf("hash: %d\t value: %s\t %s\n", hash[3], value, strcmp(value, "luz") == 0? "PASS" : "FAIL");
  value = (char*) map->entries[hash[4]]->next->next->value;
  printf("hash: %d\t value: %s\t %s\n", hash[4], value, strcmp(value, "lol") == 0? "PASS" : "FAIL");
  value = (char*) map->entries[hash[5]]->value;
  printf("hash: %d\t value: %s\t %s\n", hash[5], value, strcmp(value, "aaa") == 0? "PASS" : "FAIL");


  hash[6] = hashmap_hashcode("bbb", slots);
  hash[7] = hashmap_hashcode("zzz", slots);
  hash[8] = hashmap_hashcode("ooo", slots);
  hashmap_put(map, "bbb", "bbb");
  hashmap_put(map, "zzz", "zzz");
  hashmap_put(map, "ooo", "ooo");
  printf("\n----------------------------TEST: HASHMAP_PUT WITH RESIZE---------------\n");
  // TESTS MANQUANT

}

void test_hashmap_delete(){

}

void test_hashmap_get(){
  int slots = 10;
  t_hashmap* map = hashmap_create(slots, 0.7, 2.2);
  hashmap_put(map, "foo", "foo");
  hashmap_put(map, "bar", "bar");
  hashmap_put(map, "baz", "baz");
  hashmap_put(map, "luz", "luz");
  hashmap_put(map, "lol", "lol");
  hashmap_put(map, "aaa", "aaa");
  printf("\n----------------------------TEST: HASHMAP_GET BEFORE RESIZE---------------\n");
  printf("%s\n", strcmp((char*)hashmap_get(map, "foo"), "foo") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "bar"), "bar") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "baz"), "baz") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "luz"), "luz") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "lol"), "lol") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "aaa"), "aaa") == 0? "PASS" : "FAIL");

  hashmap_put(map, "bbb", "bbb");
  hashmap_put(map, "zzz", "zzz");
  hashmap_put(map, "ooo", "ooo");
  printf("\n----------------------------TEST: HASHMAP_GET AFTER RESIZE---------------\n");
  printf("%s\n", strcmp((char*)hashmap_get(map, "foo"), "foo") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "bar"), "bar") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "baz"), "baz") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "luz"), "luz") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "lol"), "lol") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "aaa"), "aaa") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "bbb"), "bbb") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "zzz"), "zzz") == 0? "PASS" : "FAIL");
  printf("%s\n", strcmp((char*)hashmap_get(map, "ooo"), "ooo") == 0? "PASS" : "FAIL");
}

void test_hashmap_resize(){

}

void test_json(){

/**
  * http://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
  *
  *
  */
  char** json_test_strings = malloc(sizeof(char**)*9);

  //Ne pas insérer d'espaces ??
  //On considère que les JSON strings seront stockées sans espaces ??
  // Il faut peut être s'occuper des espaces
  json_test_strings[0] = "{\"key\":\"value\"}";
  json_test_strings[1] = "{\"key\":12}";
  json_test_strings[2] = "{\"key\": 1.2}";

  json_test_strings[3] = "{ key: \"value\"}"; //error
  json_test_strings[4] = "{\"key\": }"; //error
  json_test_strings[5] = "{: }"; //error
  json_test_strings[6] = "{\"key\": "; //error
  json_test_strings[7] = "\"key\": "; //error
  json_test_strings[8] = "\"key\": }"; //error

  /** @todo test case: objet contenu dans objet */

  t_hashmap* map = JSON_parse(json_test_strings[0], NULL);
  printf("%d", strcmp(hashmap_get(map, "key"), "value") != 0);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[1], NULL);
  printf("%d", 12 == *((int*)hashmap_get(map, "key")) );
  hashmap_free(map);

  map = JSON_parse(json_test_strings[2], NULL);
  printf("%d", 1.2 == *((float*)hashmap_get(map, "key")) );
  hashmap_free(map);

  map = JSON_parse(json_test_strings[3], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[4], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[5], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[6], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[7], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

  map = JSON_parse(json_test_strings[8], NULL);
  printf("%d", map == NULL);
  hashmap_free(map);

}
