#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

void printHistory(){
}

int addList(char* commandLine, struct Hline* front){
  struct Hline* latest;
  //If we are at front of list:
  if(front->argc == 0){
    latest = front;
    //Or, we need to insert it into end.
  } else {
    latest = newHline();
    struct Hline* back = backList(front);
    back->next = latest;
  }
  //Populate the struct with recieved values.
  char* command = strtok(commandLine, " ");
  while(command != NULL){
    latest->argv[latest->argc] = strdup(command);
    latest->argc ++;
    printf("%s\n", command);
    command = strtok(NULL," ");
  }
}

//#Helper functions
//Constructor initializes a command line struct.
struct Hline* newHline(){
  struct Hline* newHline;
  newHline = (struct Hline *)malloc(sizeof(struct Hline));
  newHline -> next = NULL;
  newHline -> argc = 0;
  return(newHline);
}

//Returns a pointer to the last struct in command list.
static struct Hline* backList(struct Hline* front){
  while(front->next != NULL){
    front = front->next;
  }
  return front;
}
