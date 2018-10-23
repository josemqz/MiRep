#include "stdio.h"
#include "stdlib.h"

//Estructura de nodo
typedef struct node{
    void* data;
    char type; // "i","c","b"
    struct node* next;
}listNode;

//Estructura de lista enlazada
typedef struct {
    listNode* head;
    listNode* tail;
    listNode* curr;
    int listSize;
    int pos;
}linkList;



void moveToStart(void* Lista);
void moveToPos(int pos, linkList* List);
void next(void* List);
int getSize(void* List);
void* getRand(listNode* node);
void* generateNode();
