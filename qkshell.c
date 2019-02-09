#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

int main (){
  //Front of command history. (Linked List)
  struct Hline* front = newHline();

  //Read commands, each line being 256 max.
  char* commandLine = (char*)malloc(256);
  fgets(commandLine, 256, stdin);
  strtok(commandLine, "\n");

  //Executes it.

  // Parse it into history linked list.
  addList(commandLine, front);
  //printf("%s\n",front->argv[1]);

}

//pwd
//cd
//export
//history
//exit
