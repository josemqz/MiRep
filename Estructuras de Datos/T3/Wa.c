#include "stdio.h"
#include "stdlib.h"
#define VISITADO 1
#define VISITADONT 0
#define MAX(X,Y) ((X > Y)?(X):(Y))

typedef struct node{
    int numbr;
    struct node* next;
    int vis;
}listNode;

typedef struct {
    listNode* curr;
    listNode* head;
    listNode* tail;
    int size;
    int node;
    int visit;
}linkList;

typedef struct{
    int nVertex;
    linkList** array;
}graphList;

linkList* ListConstructor(){
    linkList* l = (linkList*)malloc(sizeof(linkList));
    l-> head = l-> tail = l-> curr = NULL;
    l-> size = 0;
    l-> visit = VISITADONT;
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

void next(linkList* l){
    if (l->curr != l->tail) {
        l->curr = l->curr->next;
    }
}

void prev(linkList* l){
    if (l->curr != l->head) {
        listNode* aux = l->curr;
        l->curr = l->head;
        while (l->curr->next != aux) {
            next(l);
        }
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
    //l->head = NULL;
    l->size = 0;
}

void destroyerL(linkList* l){
    //if (l->head != NULL) free(l->head);
    free(l);
}

void moveToStart(linkList* l) {
    l->curr = l->head;
}

void moveToEnd(linkList* l) {
    l->curr = l->tail;
}

graphList* initGraph(int vertex){
    graphList* G = (graphList*)malloc(sizeof(graphList));
    linkList** arr = (linkList**)malloc(vertex*sizeof(linkList*));
    int i;
    for (i = 0; i < vertex; i++) {
        arr[i] = ListConstructor();
        arr[i]->node = i;
    }
    G->array = arr;
    G->nVertex = vertex;
    return G;
}

void graphDestroyer(graphList* g) {
    int i;
    for (i = 0; i < g->nVertex; i++) {
        Clear(g->array[i]);                 //<<<<<<<//CHECK
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
}


void PrintGrafo(graphList* G){
    int i;
    for (i = 0; i < G->nVertex;i++){
        printf("%d\t", i);
        if (G->array[i]->head != NULL){
            for(moveToStart(G->array[i]); G->array[i]->curr != G->array[i]->tail; next(G->array[i])){
                //printf("%d\n", i);
                printf("%d ", G->array[i]->curr->numbr);
            }
                printf("%d ", G->array[i]->tail->numbr);
        }
        puts("\n");
        if (G->array[i]->visit == VISITADONT) printf("N: %d\n", G->array[i]->node);

    }
}

void VisitadontGrafo(graphList* G){
    int i;
    for (i = 0; i < G->nVertex;i++){
        printf("%d\n", i);
        G->array[i]->visit = VISITADONT;
    /*    if (G->array[i]->head != NULL){
            for(moveToStart(G->array[i]); G->array[i]->curr != G->array[i]->tail; next(G->array[i])){
                //printf("%d\n", i);
                G->array[i]->curr->vis = VISITADONT;
            }
            //if(G->array[i]->tail != NULL) {
                G->array[i]->tail->vis = VISITADONT;
            //}
        }*/
    }
}


void DFS(graphList* G, int v){

    if (!G->array[v]->curr) return;

    if (G->array[v]->visit == VISITADONT) {
        G->array[v]->visit = VISITADO;
        G->array[v]->curr->vis = VISITADO;
}

    moveToStart(G->array[v]);
    while (G->array[v]->curr != G->array[v]->tail) {
        next(G->array[v]);
        DFS(G, G->array[v]->curr->numbr);
    }
}


void Search(graphList* G, int v){

    //moveToStart(G->array[v]);
    if (G->array[v]->visit != VISITADO) {
        printf("lo visita (no estaba visitado): %d\n", v);  //no esta visitado, y visita al v :o
        G->array[v]->visit = VISITADO;

        if (G->array[v]->head != NULL){
            printf("Search(%d)\n", G->array[v]->node); //nodo no nulo siendo usada en la funcion Search

            for(moveToStart(G->array[v]);G->array[v]->curr != G->array[v]->tail;next(G->array[v])){
                //next(G->array[v]);
                printf("parametro para funcion: %d\n", G->array[v]->curr->numbr);    //numero a ser usado en la funcion recursiva
                Search(G, G->array[v]->curr->numbr);
            }
            printf("Search cola:%d\n", G->array[v]->tail->numbr);
            Search(G, G->array[v]->tail->numbr);
        }
        printf("v (termina funcion): %d visitado?:%d\n", v, G->array[v]->visit);    //termina la funcion con v
    }
}


//A -> B -> C -> D -> F
//B -> E -> D
//E -> C
//D -> E -> X
//F -> |_
//C -> |_
//Arr = {A,B,E,C,D,X,F}


void printToScreen(linkList* l){

    if(l->head == NULL){
        printf("%d\n", 0);
    }

    else{
        printf("%d ", l->size);

        for (moveToStart(l); l->curr != l->tail; next(l)){
            printf("%d ",l->curr->numbr);
        }
        printf("%d\n", l->tail->numbr);
    }
}
