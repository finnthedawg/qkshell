#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "history.h"
#include "path.h"

#define MAXLINE 1024

int emptyString(char * string);
int invokeHistory(char* commandLine);

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

  int replayHistory = 0;
  //Each time user enters a new command.
  char* commandLine;
  char* command;
  struct Hline* commandNode;
  while(1){
    printf(">> ");
    if (replayHistory == 0){
      //Store commandLine. Assume max of 1024.
      commandLine = (char*)malloc(MAXLINE);
      fgets(commandLine, MAXLINE, stdin);
      strtok(commandLine, "\n");
      if(emptyString(commandLine)){
        free(commandLine);
        continue;
      }
    }

    //If we are invoking past history, go through loop but set vars from history.
    if(invokeHistory(commandLine)){
      replayHistory = 1;
      int commandNumber = invokeHistory(commandLine);
      commandNode = findHistoryNode(front, commandNumber);
      if(commandNode == NULL){
        printf("No command found for history number: %d\n", invokeHistory(commandLine));
        replayHistory = 0;
        continue;
      }
      command = commandNode->argv[0];
      commandLine = cmdLine(commandNode);
    }

    if(replayHistory == 0){
      //Also save to history file.
      appendCommand(commandLine);
      // Parse it into history linked list.
      command = addList(commandLine, front);
      commandNode = backList(front);
    }

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
      if(chdir(commandNode->argv[1]) == -1){
        printf("qksh: %s: error changing directory\n", front->argv[1]);
      }
    }
    else if(!strcmp(command, "exit")){
      destructList(front);
      destructPaths(PathArray);
      free(commandLine);
      break;
    }
    //Check system commands in paths.
    else{
      char * foundDirectory = findCmd(PathArray, command);
      if(foundDirectory == NULL){
        printf("qksh: command %s not found\n", command);
      } else {
        printf("%s is an external command (%s)\n",command, foundDirectory);
        printf("command arguments:\n");
        int i;
        for(i = 1; i< PATHCOUNT; i++){
          if(commandNode->argv[i] == NULL){
            break;
          }
          printf("%s\n", commandNode->argv[i]);
        }
      }
      free(foundDirectory);
    }
    free(commandLine);
    //We only replay History once.
    replayHistory = 0;
  }

}

int emptyString(char * string){
  int i;
  for(i = 0; i <MAXLINE && i<strlen(string); i++){
    if(!isspace(*(string+i))){
      return(0);
    }
  }
  return(1);
}

int invokeHistory(char* commandLine){
  if(*commandLine == '!'){
    return(atoi(commandLine+1));
  } else {
    return(0);
  }
}
