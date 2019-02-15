#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"
#include "path.h"

int main (){
  //Load history from file.
  struct Hline* front = loadHistory();

  //Store paths and init first to "PATH="
  struct Path* PathArray[PATHCOUNT] = {NULL};
  struct Path* first = newPath();
  char * tempPath = strdup("PATH");
  first -> argv[0] = tempPath;
  first -> pathC = 1;
  PathArray[0] = first;

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
    if(!strcmp(command, "export")){
      //If only export, then we print the KEY;VALS.
      if(!strcmp(commandLine, "export")){
        printPath(PathArray[0]);
      } else {
        setPath(PathArray, commandLine);
      }
    }

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
