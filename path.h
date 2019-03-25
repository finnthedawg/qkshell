#ifndef PATH_H
#define PATH_H
#define PATHCOUNT 32
#define MAXLINE 1024

//Struct defining each path in history,
struct Path {
  int pathC;
  //Each PATH can have 32 directories.
  char* argv[PATHCOUNT];
};

//SetPath given the path array and commandLine
void setPath(struct Path** Paths, char* commandLine);

//SetNode of a target path node with the Paths as a string.
void setNode(struct Path* target, char* Paths);

//Deletes the array of Paths.
void destructPaths(struct Path** PathArray);

//Deletes one node
void destructNode(struct Path* node);

//Check for command file within PATH array values.
//Returns the directory where it is found
//Returns NULL if file not found
char* findCmd(struct Path** PathArray, char* file);

//Prints the paths given the array of paths.
void printPath(struct Path** target);

//Prings the target node. 0 for success, 1 for FAIL
int printPathNode(struct Path* target);

//Gets the key and valye of a target path node.
char* getNodeKeyVal(struct Path* target);

//Gets the value of a target path node.
char* getNodeVal(struct Path* target);

//Creates a empty Path node.
//Returns pointer to Path node
struct Path* newPath();

//Return pointer to Path from Path array that matches Pvar
//Returns NULL if none found.
struct Path* findPath(struct Path** Paths, char* Pvar, int size);
#endif
