#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <string.h>

#include "json.h"
#include "hashmap.h"
#include "utils.h"

/**
* @see http://www.cplusplus.com/reference/cstring
* strchr  Locate first occurrence of character in string (function )
* strrchr Locate last occurrence of character in string (function )
* strcpy  Copy string
*/


// Convert a JSON String to a HashMap representation.
t_hashmap* JSON_parse(char* string, t_hashmap* map){
  // manque trim pour supprimer les blancs au début et à la fin

  int slots = 10;
  if(map == NULL)
    map = hashmap_create(slots, 0.7, 2.2);

  unsigned size = (unsigned)strlen(string);

  // vérifier que le json est bien formé avec '{' au début et '}' à la fin
  if(string[0] != '{' || string[size] != '}')
    return NULL;

  /*********************************************
   : marque la séparation key-value (si on n'est pas dans une chaine de caractères)
   ' indique une string (si on n'est dans une chaine de caractères -> erreur?)
   . peut indiquer un float (si on n'est pas dans une chaine de caractères)
   {(123) et }(125) indiquent un objet -> récursivité du JSON_parse
  ***************************************************/
  unsigned i ;
  for(i = 1; i < size-1; i++){
    char c = string[i];
    if(c == 123){
      //recherche de l'accolade fermante
      unsigned j;
      unsigned found = 0;
      for(j=i; j<size-1; j++){
        if(c == 125){
          found = 1;
          break;
        }
      }
      //JSON mal formé
      if(0 == found) return NULL;
      // else
      char substr[j-i];
      // à tester
      substring(string, i, j-1, substr);
      JSON_parse(substr, map);
    }
    if(c == 125){

    }
    if(c == '\''){

    }
    if(c == ':'){

    }

    if(c == '.'){

    }

    // Array -> si on a le temps
    if(c == '['){
      //91
    }
    if(c == ']'){
      //93
    }

  }

  return map;
}

// int specialChar(char c){
//   if(c == 123)
//     return 0
//   if(c == 125)
//     return 1
//   if(c == '\'')
//     return 2
//   if(c == ':')
//     return  3
//   if(c == '.')
//     return 4
//
//   return -1;
// }


// Convert a HashMap to a JSON String representation.
char* JSON_stringify(t_hashmap* map){
  /***********************************************
  - Faire un tableau de key-value
  - trouver les sous-objets et les convertir (en commençant par le niveau le plus bas de la hiérarchie -> récursivité)
  - convertir les key-value au niveau racine

  le caractère . indique un sous niveau dans la hiérarchie

  *************************************************/
  int x = 1;
  char* json = malloc(sizeof(char*)*x);
  return json;
}
