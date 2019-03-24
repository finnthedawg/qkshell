#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1024
int main(){
  char* text;
  text = (char *)malloc(MAXLINE);
  fgets(text, MAXLINE, stdin);
  text = strsep(&text , "\n");
  printf("%spiped! ", text);
  fprintf(stderr, "Some error happened here\n");
}
