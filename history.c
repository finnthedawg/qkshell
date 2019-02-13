#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

int addList(char* commandLine, struct Hline* front){
  struct Hline* latest;
  //Edge case if history is empty.
  if(front->argc == 0){
    latest = front;
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

void printHistory(struct Hline* front){
  if(front == NULL){
    printf("There is no history yet.\n");
  } else {
    printHline(front);
    int counter = 1;
    while(front -> next != NULL){
      //TODO
    }
  }
}

//#Helper functions
void printHline(struct Hline* node){
  if(node == NULL){
    printf("NULL node\n");
  } else {
    for (int i = 0; i<ARGCOUNT && node -> argv[i] != NULL; i++){
      printf("%s ", node -> argv[i]);
    }
  }
}

//Constructor initializes a command line struct.
struct Hline* newHline(){
  struct Hline* newHline;
  newHline = (struct Hline *)malloc(sizeof(struct Hline));
  newHline -> next = NULL;
  newHline -> argc = 0;
  //Sets command text pointers to NULL
  for (int i = 0; i<32; i++){
    newHline -> argv[i] = NULL;
  }
  return(newHline);
}

//Returns a pointer to the last struct in command list.
static struct Hline* backList(struct Hline* front){
  while(front->next != NULL){
    front = front->next;
  }
  return front;
}
