#include "Wa.c"
#include "stdio.h"
#include "stdlib.h"

linkList* ListConstructor();
void listAppend(linkList* l, int item);
void next(linkList* l);
void prev(linkList* l);
void Clear(linkList* l);
void destroyerL(linkList* l);
void moveToStart(linkList* l);
void moveToEnd(linkList* l);
graphList* initGraph(unsigned int vertex);
void graphDestroyer(graphList* g);
int vertex(graphList* g);
void setEdge(graphList* G, int source, int dest);
