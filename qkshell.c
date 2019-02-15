#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unstd.h>

#include "history.h"
#include "path.h"

#define MAXLINE 1024

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
    char* commandLine = (char*)malloc(MAXLINE);
    fgets(commandLine, MAXLINE, stdin);
    strtok(commandLine, "\n");
    //Also save to history file.
    appendCommand(commandLine);
    // Parse it into history linked list, and store argv
    char* command = addList(commandLine, front);

    //Begin checking built in commands.
    if(!strcmp(command, "history"))
      printHistory(front);

    if(!strcmp(command, "export")){
      //If only export, then we print the exported paths.
      if(!strcmp(commandLine, "export")){
        printPath(PathArray);
      } else {
        setPath(PathArray, commandLine);
      }
    }

    if(!strcmp(command, "pwd")){
      char* wd = (char*)malloc(MAXLINE);
      wd = getcwd(wd, MAXLINE);
    }
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
