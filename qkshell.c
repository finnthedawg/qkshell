#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

int main (){
  //Load history from file.
  struct Hline* front = loadHistory();

  //Each time user enters a new command.
  while(1){
    //Store commandLine. Assume max of 1024.
    char* commandLine = (char*)malloc(1024);
    fgets(commandLine, 1024, stdin);
    strtok(commandLine, "\n");
    //Also save to history file.
    appendCommand(commandLine);
    // Parse it into history linked list, and store argv
    char* command = addList(commandLine, front);

    //Begin checking built in commands.
    if(!strcmp(command, "history"))
      printHistory(front);
    //Begin checking system commands.

    free(commandLine);
  }

  //Prints the history
  printHistory(front);

}


//pwd
//cd
//export
//history
//exit
