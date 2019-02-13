//Number of flags-2 each command can have
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
//Returns pointer to argvs.
//Inserts /0 into commandLine string's delimiters.
char* addList(char* commandLine,struct Hline* front);
//Prints the history
void printHistory(struct Hline* front);
//Appends entered command to file.
//Adds a "\n after command";
void appendCommand(char* commandLine);
//Loads the history to linked list and return pointer to front of list.
struct Hline* loadHistory();

//Helper functions
//Creates structure of a new command.
struct Hline* newHline();
//Returns a pointer to the last struct in command list.
static struct Hline* backList(struct Hline* front);
//Prints one Hline.
void printHline(struct Hline* node);
