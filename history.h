//Number of flags-2 each command can have
#define ARGCOUNT 32
#define MAXLINE 1024

//Struct defining each command in History.
struct Hline {
  int argc;
  //Each command can have 32 args
  char* argv[ARGCOUNT];
  //Store name of input file to stdin.
  char* infilename;
  //Store name of output file.
  char* outfilename;
  //Store stdout or stderr for the output;
  int fdOut;
  //The next line
  struct Hline* next;
};

//Struct definining each line in history.
struct Hcommand {
  int argc; //Assume ARGCOUNT number of piped commands.
  struct Hline* command[ARGCOUNT];
  //The next line
  struct Hcommand* next;
};

//Structure to store line containing piped commands;
void addLineHcommand(char * commandLine, struct Hcommand* front);

//Parses line and adds argvs to command history list.
//Returns pointer to argvs.
//Inserts /0 into commandLine string's delimiters.
char* addList(char* commandLine,struct Hline* front);

//Goes through and destructs list.
void destructList(struct Hline* front);

//Prints the history
void printHistory(struct Hline* front);

//Print the history including piped commands.
void printCommandHistory(struct Hcommand * frontCommandLine);

//returns the Nth node;
struct Hline* findHistoryNode(struct Hline* front, int n);

//returns the original command;
char* cmdLine(struct Hline* cmd);

//Appends entered command to file.
//Adds a "\n after command";
void appendCommand(char* historyDirectory, char* commandLine);

//Loads the history to linked list and return pointer to front of list.
struct Hline* loadHistory();

//Helper functions
//Creates structure of a new command.
struct Hline* newHline();

//Creates structues of a new piped command line
struct Hcommand* newHcommand();

//Delete structure.
void destructHline(struct Hline* node);

//Returns the last commandLine in command List.
struct Hcommand* CommandBackList(struct Hcommand* front);

//Returns a pointer to the last struct in command list.
struct Hline* backList(struct Hline* front);

//Prints one Hline.
void printHline(struct Hline* node);
