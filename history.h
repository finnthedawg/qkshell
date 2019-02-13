#define ARGCOUNT 32

//Struct defining each line in history
struct Hline {
  int argc;
  //Each command can have 32 args
  char* argv[ARGCOUNT];
  //The next line
  struct Hline* next;
};

//Parses line and adds argvs to command history list.
int addList(char* commandLine,struct Hline* front);
//Prints the history
void printHistory(struct Hline* front);

//Creates structure of a new command.
struct Hline* newHline();
//Returns a pointer to the last struct in command list.
static struct Hline* backList(struct Hline* front);
//Prints one Hline.
void printHline(struct Hline* node);
