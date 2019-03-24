#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h> // for open()
#include <unistd.h>  //For close()
#include <sys/types.h>
#include <sys/wait.h> //For wait() on the parent for child

#include "history.h"
#include "path.h"

#define MAXLINE 1024

//If string doesnt have space, return 0 else return 1
int emptyString(char * string); //Check
//Returns the history number of a !34, or 0 if there is no invoking of history
int invokeHistory(char* commandLine);
//Expands our string by expanding PATH variables and PWD variable.
char* expandVariable(char *string, struct Path* PathArray, char* PWDvariable);

int main (){
  //This is the linked list of piped commands
  struct Hcommand* frontCommandLine = loadHistory();

  //Store paths and init first to nlll.
  struct Path* PathArray[PATHCOUNT] = {NULL};
  //Creates a empty Path node, struct PATH.
  struct Path* first = newPath();
  //This is the first path.
  char * tempPath = strdup("PATH");
  first -> argv[0] = tempPath;
  first -> pathC = 1;
  PathArray[0] = first;
  //This is the PWDvariable.
  char * PWDvariable = (char*)malloc(MAXLINE);
  PWDvariable = getcwd(historyDirectory, MAXLINE);

  //Remember where the history.txt is located.
  char* historyDirectory = (char*)malloc(MAXLINE);
  historyDirectory = getcwd(historyDirectory, MAXLINE);
  strcat(historyDirectory, "/history.txt");

  int replayHistory = 0;
  //This is the full line (piped)
  char* commandLine;
  char* command; //This is the actual command of each command.
  struct Hcommand* commandNode; //This is the piped command in Hcommand format.
  while(1){
    printf(">> ");
    //If we are not replaying history, we can simply run this.
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
      int commandNumber = invokeHistory(commandLine); //Gets the command number from our entered command.
      commandNode = findHistoryPiped(frontCommandLine, commandNumber);
      if(commandNode == NULL){
        printf("No command found for history number: %d\n", invokeHistory(commandLine));
        replayHistory = 0;
        continue;
      }
      command = strdup(commandNode -> command[0] -> argv[0]);
      //We take the first command of the pipe as "command Line" for now.
      commandLine = cmdLine(commandNode -> command[0]);
    }

    //If we are not invoking history, then we set the correct data structures to our read commandLine.
    if(replayHistory == 0){
      //Write the line to the history file.
      appendCommand(historyDirectory, commandLine);
      // Parse it into linked list.
      addLineHcommand(commandLine, frontCommandLine);
      //Retrieve the command.
      commandNode = CommandBackList(frontCommandLine);
      command = strdup(commandNode -> command[0] -> argv[0]);
    }

    if(!strcmp(command, "exit")){
      destructList(frontCommandLine);
      free(historyDirectory);
      free(commandLine);
      return(0);
    }

    //Now we check the piped commands.
    int p[2]; //This is our pipe.
    pid_t pid; //Process ID
    int fd_in = 0; //The input filedescriptor

    int i, j;
    //While our commandNode contains commands
    for (i = 0; commandNode -> command[i] != NULL; i++){

      //Scan through the arguments and expand the variables.
      for (j = 0; commandNode -> command[i] -> argv[j] != NULL; j++){
        expandVariable(commandNode -> command[i] -> argv[j]);
      }

      //If we only have one command, then run it.
      //We only need to do this for commands (export and cd) that change the environment varables.
      if(i == 0 && commandNode -> command[1] == NULL){
        if(!strcmp(commandNode -> command[i] -> argv[0], "export")){
          //If only export, then we print the exported paths.
          if(!strcmp(commandLine, "export")){
            printPath(PathArray);
          } else {
            setPath(PathArray, commandLine);
          }
          continue;
        }
        else if(!strcmp(commandNode -> command[i] -> argv[0], "cd")){
          if(chdir(commandNode->command[0]->argv[1]) == -1){
            printf("qksh: %s: error changing directory\n", frontCommandLine->command[0]->argv[1]);
          }
          continue;
        }
      }

      pipe(p); //Create the pipe for communication.
      //The child process.
      if ( (pid = fork()) == 0){
        dup2(fd_in,0); //stdin becomes fd_in.
        if (commandNode -> command[i+1] != NULL){ //If we have more commands.
          dup2(p[1],1); //set the write end of pipe to stdout of process.
        }
        close(p[0]); //Close the read end.

        //Change the 0 and 1 away from the pipes and fd_in if we have redirection
        if (commandNode -> command[i] -> infilename != NULL){
          int infd = open(commandNode -> command[i] -> infilename, O_RDONLY);
          if (infd == -1 ){
            fprintf(stderr, "Input file %s could not be opened", commandNode -> command[i] -> infilename);
          } else {
            dup2(infd, 0); //Set stdin to the opened fd.
          }
        }
        if (commandNode -> command[i] -> outfilename != NULL){
          int infd = open(commandNode -> command[i] -> outfilename,O_WRONLY | O_CREAT | O_TRUNC, 0666); //Open and truncate original content
          if (infd == -1 ){ //If there was an error.
            fprintf(stderr, "Output file %s could not be opened", commandNode -> command[i] -> outfilename);
          } else {
            dup2(infd, commandNode -> command[i] -> fdOut); //Set the stream we want to the output file's fd.
          }
        }
        //Here we should check for built in commands.
        if(!strcmp(commandNode -> command[i] -> argv[0], "history")){
          printCommandHistory(frontCommandLine);
          return(0);
        }
        else if(!strcmp(commandNode -> command[i] -> argv[0], "export")){
          //If only export, then we print the exported paths.
          if(!strcmp(commandLine, "export")){
            printPath(PathArray);
          } else {
            setPath(PathArray, commandLine);
          }
          return(0);
        }
        else if(!strcmp(commandNode -> command[i] -> argv[0], "pwd")){
          char* wd = (char*)malloc(MAXLINE);
          wd = getcwd(wd, MAXLINE);
          printf("%s\n",wd);
          return(0);
        }
        else if(!strcmp(commandNode -> command[i] -> argv[0], "cd")){
          if(chdir(commandNode->command[0]->argv[1]) == -1){
            printf("qksh: %s: error changing directory\n", frontCommandLine->command[0]->argv[1]);
          }
          return(0);
        }
        else{
          char * foundDirectory = findCmd(PathArray, commandNode -> command[i] -> argv[0]);
          if(foundDirectory == NULL){
            printf("qksh: command %s not found\n", commandNode -> command[i] -> argv[0]);
            return(0);
          } else {
            execvp(foundDirectory, commandNode -> command[i] -> argv);
          }
        }
      } else{ //The "joining" process.
        wait(NULL); //Parent will wait for child to finish executing.
        close(p[1]); //Close the write end of pipe.
        fd_in = p[0]; //fd_in will be set to the read end of pipe. Next process will use this to set stdin.
      }

    }

    //We only replay History once.
    replayHistory = 0;
  }
}

//Expands our string by expanding PATH variables and PWD variable.
char* expandVariable(char *string, struct Path* PathArray, char* PWDvariable){
  if strstr()
}

//If string doesnt have space, return 0 else return 1
int emptyString(char * string){
  int i;
  for(i = 0; i <MAXLINE && i<strlen(string); i++){
    if(!isspace(*(string+i))){
      return(0);
    }
  }
  return(1);
}

//Returns the history number of a !34, or 0 if there is no invoking of history
int invokeHistory(char* commandLine){
  if(*commandLine == '!'){
    return(atoi(commandLine+1));
  } else {
    return(0);
  }
}
