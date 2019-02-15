#ifndef PATH_H
#define PATH_H
#define PATHCOUNT 32

//Struct defining each path in history,
struct Path {
  int pathC;
  //Each PATH can have 32 directories.
  char* argv[PATHCOUNT];
};

//Prints the paths given the array of paths.
void printPath(struct Path** target);

//SetPath given the path array and commandLine
void setPath(struct Path** Paths, char* commandLine);

//SetNode of a target path node with the Paths as a string.
void setNode(struct Path* target, char* Paths);

//Helper functions

//Prings the target node. 0 for success, 1 for FAIL
int printPathNode(struct Path* target);
//Creates a empty Path node.
//Returns pointer to Path node
struct Path* newPath();
//Return pointer to Path from Path array that matches Pvar
//Returns NULL if none found.
struct Path* findPath(struct Path** Paths, char* Pvar, int size);
#endif
