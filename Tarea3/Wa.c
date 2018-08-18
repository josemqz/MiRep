#include "stdio.h"
#include "stdlib.h"

typedef struct node{
    int numbr;
    struct node* next;
}listNode;

typedef struct {
    listNode* curr;
    listNode* head;
    listNode* tail;
    unsigned int size;
    unsigned int pos;
}linkList;

typedef struct{
    unsigned int nVertex;
    linkList** array;
}graphList;

linkList* ListConstructor(){
    linkList* l = (linkList*)malloc(sizeof(linkList));
    l-> head = l-> tail = l-> curr = NULL;
    l-> size = 0;
    l-> pos = 0;
    return l;
}

void listInsert(linkList* l, int item){
    if (l->head == NULL) {
        l->curr = l->head = l->tail = (listNode*)malloc(sizeof(listNode));
        l->curr->numbr = item;
    }
    else{
        listNode* aux = l->curr->next;
        l->curr->next = (listNode*)malloc(sizeof(listNode));
        l->curr->next->numbr = item;
        if (l->tail == l->curr) {
            l->curr->next->next = NULL;
            l->tail = l->curr->next;
        }
        else l->curr->next->next = aux;
    }
    l->size++;
}

void next(linkList* l) {
    if (l->curr != l->tail) {
        l->curr = l->curr->next;
        l->pos++;
    }
}

void prev(linkList* l){
    if (l->curr != l->head) {
        listNode* aux = l->curr;
        l->curr = l->head;
        while (l->curr->next != aux) {
            next(l);
            l->pos--;
        }
        l->pos--;
    }
}

void Clear(linkList* l){
    listNode* node = l->head;
    listNode* nxt;
    while (node != NULL) {
        nxt = node->next;
        free(node);
        node = nxt;
    }
    l->head = NULL;
    l->size = 0;
    l->pos = 0;
}

void destroyerL(linkList* l){
    if (l->head != NULL) free(l->head);
    free(l);
}

void moveToStart(linkList* l) {
    l->curr = l->head;
    l->pos = 0;
}

void moveToEnd(linkList* l) {
    l->curr = l->tail;
    l->pos = l->size - 1;
}

graphList* initGraph(unsigned int vertex){  //podriamos tratar los structs directamente en vez de usar punteros
    graphList* G = (graphList*)malloc(sizeof(graphList));
    linkList** arr = (linkList**)malloc(vertex*sizeof(linkList*));
    unsigned int i;
    for (i = 0; i < vertex; i++) {
        arr[i] = ListConstructor();
    }
    G->array = arr;
    G->nVertex = vertex;
    return G;
}

void graphDestroyer(graphList* g) {
    unsigned int i;
    for (i = 0; i < g->nVertex; i++) {
        Clear(g->array[i]);
        destroyerL(g->array[i]);
    }
    free(g->array);
    free(g);
}

int vertex(graphList* g) {
    return g->nVertex;
}

void setEdge(graphList* G, int source, int dest){
    listInsert(G->array[source], dest);
//    listInsert(G->array[dest], source); //CHECK
}


//DFS(G,v){}
