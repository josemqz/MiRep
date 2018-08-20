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
    int pos;
}linkList;

typedef struct{
    int nVertex;
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

void next(linkList* l){
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

graphList* initGraph(int vertex){
    graphList* G = (graphList*)malloc(sizeof(graphList));
    linkList** arr = (linkList**)malloc(vertex*sizeof(linkList*));
    int i;
    for (i = 0; i < vertex; i++) {
        arr[i] = ListConstructor();
        listInsert(arr[i],i);
    }
    G->array = arr;
    G->nVertex = vertex;
    return G;
}

void graphDestroyer(graphList* g) {
    int i;
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
//    listInsert(G->array[dest], source);
}



linkList* SearchEkono(graphList* G, int v, linkList* LArry){

    if (G->array[v]->curr->vis != VISITADO || G->array[v]->head->vis != VISITADO) {
                    //NODOS SON DISTINTOOOOOOOS
        G->array[v]->curr->vis = VISITADO;

        listInsert(LArry, G->array[v]->curr->numbr);
        //printf("c: %d\n", G->array[v]->curr->numbr);

        while(G->array[v]->curr != G->array[v]->tail){
            next(G->array[v]);
            SearchEkono(G, G->array[v]->curr->numbr, LArry);
        }
    }    return LArry;
}
//        printf("curr(%d): %d\n",v, G->array[v]->curr->numbr);
//puts("A");
//A -> B -> C -> D -> F
//B -> E -> D
//E -> C
//D -> E -> X
//F -> |_
//C -> |_
//Arr = {A,B,E,C,D,X,F}


void removeFromAdjList(linkList* L, int item){

    for (moveToStart(L); L->curr != L->tail; next(L)) {
        if (L->curr->numbr == item) {
            listNode* CurrHolder;
            listNode* aux;
            aux = L->curr;
            CurrHolder = L->curr->next;
            prev(L);
            L->curr->next = CurrHolder;
            free(aux);
            L->size--;
        }
    }
}

linkList* finalList(int nodosGrafo, linkList* alcanzables, linkList* list){
    int i;

    for (i = 0; i < nodosGrafo; i++) {
        listInsert(list,i);
    }
    moveToStart(list);

    for (i = 0; i < nodosGrafo; i++) {

        for (moveToStart(alcanzables); alcanzables->curr != alcanzables->tail; next(alcanzables)) {

          if(i == alcanzables->curr->numbr) removeFromAdjList(list,i);
        }
    }
    return list;
}

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

//BOOM!
