#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){
  //Each line in history
  struct Hline {
    int argc;
    //Each command can have 32 args.
    char* argv[32];
    //The next line
    struct Hline* next;
  };

  //Constructor
  struct Hline* newHline(){
    struct Hline* newHline;
    newHline = (struct Hline *)malloc(sizeof(struct Hline));
    newHline -> next = NULL;
    newHline -> argc = 0;
    return(newHline);
  }

  struct Hline* base = newHline();
  struct Hline* current = newHline();

  //Read commands, each line being 256 max.
  char* commandLine = (char*)malloc(256);
  fgets(commandLine, 256, stdin);
  strtok(commandLine, "\n");

  //Executes it.

  // Parse it into history linked list.
  struct Hline* latest = newHline();
  char* command = strtok(commandLine, " ");
  while(command != NULL){
    latest->argv[latest->argc] = strdup(command);
    latest->argc ++;
    printf("%s\n", command);
    command = strtok(NULL," ");
  }
  //Shift pointer to next argument
  current->next = latest;
  current = latest;
}

//pwd
//cd
//export
//history
//exit
