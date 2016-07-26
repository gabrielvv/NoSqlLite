#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

#include "json.h"
#include "hashmap.h"
#include "cli.h"
#include "nosql.h"

// https://openclassrooms.com/courses/mettez-des-accents-dans-vos-programmes-avec-le-type-wchar-t

/**************************************************

collection: identifie la collection sur laquelle on va effectuer les autres actions - si pas de collection -> abort

Action:
  - insert:     ajout d'un élément
  - set:        ajout d'une propriété ou MAJ - peut être utilisé avec "where"
  - find:       fonction de recherche pour affichage - peut être utilisé avec "projection" et "sort"
  - remove:     suppression d'un élément

Options:
  - where:      précise les éléments sur lesquels on veut effectuer l'action - fonctionne avec "set" et "remove"
  - projection: défini les propriétés qu'on veut voir apparaitre à l'affichage
  - sort:       trie les objets


***************************************************/

/*
  130 = é
  133 = à
  138 = è
  135 = ç
  136 = ê  */


void print_help(){
  printf("Usage: NoSqlLite ?????????\n");
  printf("\nChoisir une collection :");
  printf("\n\t--collection\tname");
  printf("\nActions :");
  printf("\n\t--insert\tjson");
  printf("\n\t--set\t\tjson");
  printf("\n\t--find\t\tjson");
  printf("\nOptions :");
  printf("\n\t--where\t\tjson\ten conjonction avec --set et --remove pour retrecir le champ d'action");
  printf("\n\t--projection\tjson\ten conjonction avec --find pour definir les proprietes a afficher");
  printf("\n\t--sort\t\tjson\ten conjonction avec --find");
  printf("\n");
}

void handleArgs(int argc, char* argv[]){

  unsigned i;
  char* collection = NULL;
  char* action_arg = NULL;
  int action_index = 0;
  int option_index = 0;
  char* option_arg = NULL;
 /**
  * Les fonctions nosql nécessitent un nom de collection et une action
  * soit 5 arguments minimum avec le nom du programme
  *
  */
  if(
      (argc >= 1 && argc <= 4) ||
      (argc == 2 && strcmp(argv[1], "--help") == 0)
    ){
      print_help();
  }

  if(argc%2 == 0){
    printf("Missing arguments\nuse --help to learn how to use the NoSqlLite command line tool");
  }

  if(argc == 5 || argc == 7){
    /** On recherche l'argument collection */
    for(i = 1; i < argc-1; i=i+2){
      /** collection et action ne peuvent pas être le dernier argument */
      if(strcmp(argv[i], "--collection") == 0){
        collection = argv[i+1];
        continue;
      }
      /******************************* action ****************************/
      if(strcmp(argv[i], "--insert") == 0){
        action_arg = argv[i+1];
        action_index = 0;
        continue;
      }
      if(strcmp(argv[i], "--find") == 0){
        action_arg = argv[i+1];
        action_index = 10;
        continue;
      }
      if(strcmp(argv[i], "--remove") == 0){
        action_arg = argv[i+1];
        action_index = 20;
        continue;
      }
      if(strcmp(argv[i], "--set") == 0){
        action_arg = argv[i+1];
        action_index = 30;
        continue;
      }
      /******************************* option ****************************/
      if(argc == 7){
        if(strcmp(argv[i], "--where") == 0){
          option_arg = argv[i+1];
          option_index = 1;
          continue;
        }
        if(strcmp(argv[i], "--sort") == 0){
          option_arg = argv[i+1];
          option_index = 2;
          continue;
        }
        if(strcmp(argv[i], "--projection") == 0){
          option_arg = argv[i+1];
          option_index = 3;
          continue;
        }
      }
    }

  }//argc == 5 || argc == 7

  // 8 possibilités
  int sum = action_index + option_index;

  if(sum == 0)
    nosql_insert(collection, action_arg);

  if(sum == 10)
    nosql_find(collection, action_arg);

  if(sum == 12)
    nosql_find_sort(collection, action_arg, option_arg);

  if(sum == 13)
    nosql_find_projection(collection, action_arg, option_arg);

  if(sum == 20)
    nosql__remove(collection, action_arg);

  if(sum == 21)
    nosql_remove_where(collection, action_arg, option_arg);

  if(sum == 30)
    nosql_set(collection, action_arg);

  if(sum == 31)
    nosql_set_where(collection, action_arg, option_arg);

}
