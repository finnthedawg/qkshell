#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

//Parses line and breaks it up by pipes.
void addLineHcommand(char * commandLine, struct Hcommand* front){
  char * commandLineDup = strdup(commandLine);
  struct Hcommand* latest;
  //Edge case if history is empty.
  if(front -> argc == 0){
    latest = front;
  } else {
    latest = newHcommand();
    struct Hcommand * back = CommandBackList(front);
    back -> next = latest;
  }

  //Break up the the line into individual commands based on |
  //We assume we don't have two pipes || together.
  char* command = strsep(&commandLineDup, "|");

  while(command != NULL){
    //We are storing the command
    struct Hline* newCommandHline =  newHline();
    latest -> command[latest -> argc] = newCommandHline;
    addList(command, latest -> command[latest->argc]);
    //Increase the number of piped commands we have in Hcommand List.
    //struct Hline* command[ARGCOUNT];
    latest->argc ++;
    command = strsep(&commandLineDup,"|");
  }
  return;
}


//Parses line and adds argvs to command history list.
//Returns pointer to argvs.
//Inserts /0 into commandLine string's delimiters.
char* addList(char* commandLine, struct Hline* front){
  char * commandLineDup = strdup(commandLine);
  struct Hline* latest;
  //Edge case if history is empty.
  if(front->argc == 0){
    latest = front;
  } else {
    latest = newHline();
    struct Hline* back = backList(front);
    back->next = latest;
  }

  char* command = strtok(commandLineDup, " ");
  //Store value of first command.
  char* first = strdup(command);
  while(command != NULL){
    latest->argv[latest->argc] = strdup(command);
    latest->argc ++;
    command = strtok(NULL," ");
    //Check for redirected input or outputs.
    //If found, we set the infile name and skip adding it to the argvs
    if(command != NULL && strcmp(command, "<") == 0){
      command = strtok(NULL," ");
      latest->infilename = strdup(command);
      command = strtok(NULL," ");
    }
    if (command != NULL && strcmp(command, ">") == 0){
      command = strtok(NULL," ");
      latest->outfilename = strdup(command);
      command = strtok(NULL," ");
    }
  }
  free(commandLineDup);
  return(first);
}

//Prints the piped command history given the command.
void printCommandHistory(struct Hcommand * frontCommandLine){
  if(frontCommandLine == NULL){
    printf("There is no history set");
  } else{
    //This counts each commandLine
    int count = 1;
    while(1){
      //Increment each command per line.
      int i = 0;
      printf("%d ", count);
      //For each command we call printline
      printHline(frontCommandLine -> command[i]);
      while(frontCommandLine -> command[i+1] != NULL && printf("| ")){
        i++;
        printHline(frontCommandLine -> command[i]);
      }
      printf("\n");
      //Move the current front as we print
      if(frontCommandLine -> next == NULL){
        break;
      } else {
        frontCommandLine = frontCommandLine -> next;
      }
      //Increment to next commandLine
      count ++;
    }

  }
}


// //Prints the history given the front of the command..
// void printHistory(struct Hline* front){
//   if(front == NULL){
//     printf("There is no history yet.\n");
//   } else {
//     int count = 1;
//     printf(" %d ", count);
//     printHline(front);
//     printf("\n");
//     while(front -> next != NULL && count++){
//       front = front -> next;
//       printf(" %d ", count);
//       printHline(front);
//       printf("\n");
//     }
//     return;
//   }
// }

//Appends entered command to file.
//Adds a "\n after command";
void appendCommand(char* historyDirectory, char* commandLine){
  FILE *fp = fopen(historyDirectory,"a");
  fprintf(fp,"%s\n",commandLine);
  fclose(fp);

}

struct Hcommand* loadHistory(){
  struct Hcommand* front = newHcommand();
  FILE *fp = fopen("history.txt","r");
  if(fp != NULL){
    char* commandLine = (char*)malloc(1024);
    while(fgets(commandLine, 1024, fp)){
      strtok(commandLine, "\n");
      addLineHcommand(commandLine, front);
    }
    free(commandLine);
    fclose(fp);
  }
  return(front);
}

// //Loads the history normally.
// struct Hline* loadHistory(){
//   struct Hline* front = newHline();
//
//   FILE *fp = fopen("history.txt","r");
//   if(fp != NULL){
//     char* commandLine = (char*)malloc(1024);
//     while(fgets(commandLine, 1024, fp)){
//       strtok(commandLine, "\n");
//       addList(commandLine, front);
//     }
//     free(commandLine);
//     fclose(fp);
//   }
//   return(front);
// }

//#Helper functions
void printHline(struct Hline* node){
  if(node == NULL){
    printf("NULL node\n");
  } else {
    int i;
    for (i = 0; i<ARGCOUNT && node -> argv[i] != NULL; i++){
      printf("%s ", node -> argv[i]);
    }
  }
}

//Constructor initializes a command node struct.
struct Hline* newHline(){
  struct Hline* newHline;
  newHline = (struct Hline *)malloc(sizeof(struct Hline));
  newHline -> next = NULL;
  newHline -> argc = 0;
  newHline -> infilename = NULL;
  newHline -> outfilename = NULL;
  newHline -> fdOut = 0;
  //Sets argv text pointers to NULL
  int i;
  for (i = 0; i<ARGCOUNT; i++){
    newHline -> argv[i] = NULL;
  }
  return(newHline);
}

//Store our struct with various piped commands here.
struct Hcommand* newHcommand(){
  struct Hcommand* newHcommand;
  newHcommand = (struct Hcommand *)malloc(sizeof(struct Hcommand));
  newHcommand -> argc = 0;
  newHcommand -> next = NULL;
  //We dont have any commands in our Hcommand line. We set each it NULL
  int i;
  for (i = 0; i<ARGCOUNT; i++){
    newHcommand -> command[i] = NULL;
  }
  return newHcommand;
}

void destructHline(struct Hline* node){
  int i;
  for (i = 0; i<ARGCOUNT; i++){
    free(node -> argv[i]);
  }
  free(node -> infilename);
  free(node -> outfilename);
  free(node);
}

void destructHcommand(struct Hcommand* node){
  int i;
  for (i = 0; (node -> command[i]) != NULL; i++){
    destructHline(node -> command[i]);
  }
  free(node);
}

void destructList(struct Hcommand* front){
  struct Hcommand* seek;
  while(front->next != NULL ){
    seek = front->next;
    destructHcommand(front);
    front = seek;
  }
  destructHcommand(front);
}

//Returns the last commandLine in command List.
struct Hcommand* CommandBackList(struct Hcommand* front){
  while(front->next != NULL){
    front = front->next;
  }
  return front;
}

//Returns a pointer to the last struct in command list.
struct Hline* backList(struct Hline* front){
  while(front->next != NULL){
    front = front->next;
  }
  return front;
}

//Gets the history node including piped commands.
struct Hcommand* findHistoryNode2(struct Hcommand* front, int n){
  int i;
  for(i = 1;front -> next != NULL; i++){
    if(i == n){
      return(front);
    }
    front = front -> next;
  }
  if(i == n){
    return (front);
  }
  return(NULL);
}

struct Hline* findHistoryNode(struct Hline* front, int n){
  int i;
  for(i = 1;front -> next != NULL; i++){
    if(i == n){
      return(front);
    }
    front = front -> next;
  }
  if(i == n){
    return (front);
  }
  return(NULL);
}

char* cmdLine(struct Hline* cmd){

  char * commandLine = (char *)calloc(MAXLINE, sizeof(char));
  char * space = (char *)malloc(2);
  *space = ' ';
  *(space+1) = '\0';
  int i;
  for(i = 0; i < ARGCOUNT && cmd->argv[i] != NULL; i++){
    strcat(commandLine, cmd->argv[i]);
    //Dont insert space in last value
    if(cmd->argv[i+1] != NULL){
      strcat(commandLine, space);
    }
  }
  free(space);
  return(commandLine);
}
