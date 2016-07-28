#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hashmap.h"
#include "json.h"
#include "cli.h"
#include "nosql.h"
#include "utils.h"

void test_hashmap_put();
void test_hashmap_get();
void test_json();
void test_nosql();
void test_utils();

int main(int argc, char* argv[]){
  int mode = 1;

  if(mode == 1){
    /**************************** NOSQL LITE **************************/
    handleArgs(argc, argv);
  }

  return 0;
}
