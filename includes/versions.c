#include "versions.h"
#include "global.c"

int existTableVersions(){
  // Lecture de la table
  int *sqlResult = TableExist("select 1 from `versions` LIMIT 1");
  if(*sqlResult == 1){
    return 1;
  }else{
    return 0;
  }
}