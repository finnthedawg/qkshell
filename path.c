#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setPath(struct Path** Paths, char* commandLine){
  //So we don't modify original commandLine
  char* commandLineDup = strdup(commandLine);

  //Remove the export keyword.
  strtok(commandLineDup, " ");

  //Break up commandLine.
  char* Pname = strtok(NULL, "=");
  if(strlen(Pname) == 0){
    printf("Please specify a path name after export.");
    return;
  } else {
    Pname = strdup(Pname);
  }

  char* Pval = strtok(NULL, "\0");
  if(Pval == NULL || strlen(Pval) == 0){
    printf("Please specify values for your path using =p1:p2:p3");
    return;
  } else {
    Pval = strdup(Pval);
  }

  free(commandLineDup);

  //Now find the respective struct Path* from the Path array. Or give the next empty one.
  for(int i = 0; i < PATHCOUNT; i++){
    if(Paths[i] == NULL){
      Paths[i] = newPath();
      Paths[i]->argv[0] = Pname;
      Paths[i]->pathC = Paths[i]->pathC + 1;
      setNode(Paths[i], Pval);
      free(Pval);
      return;
    }
    //If this path is already defined
    if(!strcmp(Paths[i]->argv[0], Pname)){
      //Release the original memory
      free(Paths[i]->argv[0]);
      Paths[i]->argv[0] = Pname;
      setNode(Paths[i], Pval);
      free(Pval);
      return;
    }
  }
  //Paths are full
  printf("You have too many paths set");
  return;

}

void setNode(struct Path* target, char* Paths){
  char* Pval = strtok(Paths, ":");
  while(Pval != NULL && strlen(Pval) != 0){
    Pval = strdup(Pval);
    target->argv[target -> pathC] = Pval;
    target->pathC = target->pathC + 1;
    Pval = strtok(NULL, ":");
  }
  return;
}

struct Path* newPath(){
  struct Path* newPath;
  newPath = (struct Path *)malloc(sizeof(struct Path));
  newPath -> pathC = 0;
  //Sets directories related to this path to NULL for now.
  for (int i = 0; i<PATHCOUNT; i++){
    newPath -> argv[i] = NULL;
  }
  return(newPath);
}

void printPath(struct Path** PathArray){
  for(int i = 0; i<PATHCOUNT; i++){
    if(printPathNode(PathArray[i]) == 1){
      break;
    }
  }
  return;
}

int printPathNode(struct Path* target){
  if(target == NULL){
    return(1);
  } else {
    printf("%s=", target -> argv[0]);
    for (int i = 1; i<PATHCOUNT && target -> argv[i] != NULL; i++){
      (target -> argv[i+1] != NULL ? printf("%s:", target -> argv[i]) : printf("%s", target -> argv[i]));
    }
    printf("\n");
  }
  return(0);
}

struct Path* findPath(struct Path** Paths, char* Pvar, int size){
  for(int i = 0; i< size; i++){
    if(!strcmp(Paths[i] -> argv[0], Pvar)){
      return(Paths[i]);
    }
  }
  return(NULL);
}
