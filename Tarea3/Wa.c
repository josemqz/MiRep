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
    int* visited;
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
    //G->visited = (int*)malloc(sizeof(int));
    for (i = 0; i < vertex; i++) {
        arr[i] = ListConstructor();
        listInsert(arr[i],i);
        //G->visited[i] = 0;
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

    //free(g->visited);
}

int vertex(graphList* g) {
    return g->nVertex;
}

void setEdge(graphList* G, int source, int dest){
    listInsert(G->array[source], dest);
//    listInsert(G->array[dest], source); //CHECK
}



linkList* SearchEkono(graphList* G, int v, linkList* LArry){

    if (G->array[v]->curr->vis != VISITADO) {
        //printf("%d\n", );
        G->array[v]->curr->vis = VISITADO;

        listInsert(LArry,G->array[v]->curr->numbr);

    //A(0) -> B(1) -> C(6)(5) -> D(6)(5) -> F (6)
    //B -> E(2) -> D(4)s
    //E -> C(3)
    //D -> E(5)(4) -> X(5)
    //F -> |_
    //C -> |_
    //Arr = {A,B,E,C,D,X,F}

        while(G->array[v]->curr != G->array[v]->tail){

            printf("curr(%d): %d\n",v, G->array[v]->curr->numbr);

            next(G->array[v]);
            SearchEkono(G, G->array[v]->curr->numbr, LArry);
        }
    }
    return LArry;
}


void removeFromAdjList(linkList* L, int item){
    moveToStart(L);
    while (L->curr != L->tail) {
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
        next(L);
    }

}
/*
void Remove(tLista* L){
    if (L->act == L->head){
        free(L->head);
        L->act = L->head = L->act->sig;
    }
    else{
        Prev(L);
        L->act->sig = L->act->sig->sig;
        L->act->sig = NULL; //pa que no webee valgrind ldfjsk
        free(L->act->sig);
    }
    L->ListSize--;
}
*/

linkList* finalList(int* A, int nodosGrafo, int* B, int alcanzables){
    int i,j;
    linkList* list = ListConstructor();
    for (i = 0; i < nodosGrafo; i++) {
        listInsert(list,A[i]);
    }
    for (i = 0; i < nodosGrafo; i++) {
        for (j = 0; j < alcanzables; j++) {
          if(A[i] == B[j]){
              removeFromAdjList(list,A[i]);
          }
        }
    }
    return list;
}

void printToScreen(linkList* l){
    if(l->head == NULL){
        printf("%d\n", 0);
    }
    else{
        moveToStart(l);

        printf("%d ", l->size);

        while (l->curr != l->tail) {
            printf("%d ",l->curr->numbr);
            next(l);
        }
        printf("%d\n", l->tail->numbr);
    }
}



//Va a ir revisando nodos, partiendo del v, para así ver a los que se puede llegar desde este.
    //Parte con él y sigue a la posicion del arreglo correspondiente a cada nodo directamente conectado a v.
        //if ->next == NULL terminar busqueda (así es recursiva)
    //De ahí continúa la búsqueda a través de la lista enlazada.
//Hay que ir metiendo los nodos a una estructura, un arreglo.
//Una vez termine la busqueda, habría que hacer otro arreglo con todos los nodos e ir eliminando los existentes en el
//otro arreglo. Ojalá no sea muy costoso.
//Retorna este arreglo final, el cual deberá ser introducido al archivo de texto.
//BOOM!
