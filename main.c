#include <stdio.h>
#include "hashmap.h"
#include "json.h"
#include "cli.h"
#include "nosql.h"

int main(){
  char json[] = "{ name : 'Gabriel', rate : 12,  group : 'AL2' }";
  JSON_parse(json);
  return 0;
}
