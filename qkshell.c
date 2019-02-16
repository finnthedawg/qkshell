#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "history.h"
#include "path.h"

#define MAXLINE 1024

int emptyString(char * string);
void exitShell();

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
    printf(">> ");
    //Store commandLine. Assume max of 1024.
    char* commandLine = (char*)malloc(MAXLINE);
    fgets(commandLine, MAXLINE, stdin);
    strtok(commandLine, "\n");
    if(emptyString(commandLine)){
      free(commandLine);
      continue;
    }
    //Also save to history file.
    appendCommand(commandLine);
    // Parse it into history linked list, and store argv
    char* command = addList(commandLine, front);

    //Begin checking built in commands.
    if(!strcmp(command, "history")){
      printHistory(front);
    }

    else if(!strcmp(command, "export")){
      //If only export, then we print the exported paths.
      if(!strcmp(commandLine, "export")){
        printPath(PathArray);
      } else {
        setPath(PathArray, commandLine);
      }
    }

    else if(!strcmp(command, "pwd")){
      char* wd = (char*)malloc(MAXLINE);
      wd = getcwd(wd, MAXLINE);
      printf("%s\n",wd);
    }

    else if(!strcmp(command, "cd")){
      if(chdir(backList(front)->argv[1]) == -1){
        printf("qksh: %s: error changing directory\n", front->argv[1]);
      }
    }
    else if(!strcmp(command, "exit")){
      free(commandLine);
      void exitShell();
    }
    //Check system commands in paths.
    else{
      char * foundDirectory = findCmd(PathArray, command);
      if(foundDirectory == NULL){
        printf("qksh: command %s not found\n", command);
      } else {
        printf("%s is an external command (%s)\n",command, foundDirectory);
        printf("command arguments:\n");
        for(int i = 1; i< PATHCOUNT; i++){
          if(backList(front)->argv[i] == NULL){
            break;
          }
          printf("%s\n", backList(front)->argv[i]);
        }
      }
      free(foundDirectory);
    }
    free(commandLine);
  }

  //Prints the history
  printHistory(front);

}

int emptyString(char * string){
  for(int i = 0; i <MAXLINE && i<strlen(string); i++){
    if(!isspace(*(string+i))){
      return(0);
    }
  }
  return(1);
}

void exitShell(){
  return;
}
