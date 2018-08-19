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
    G->visited = (int*)malloc(sizeof(int));
    for (int i = 0; i < vertex; i++) {
        arr[i] = ListConstructor();
        G->visited[i] = 0;
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

    free(g->visited);
}

int vertex(graphList* g) {
    return g->nVertex;
}

void setEdge(graphList* G, int source, int dest){
    listInsert(G->array[source], dest);
//    listInsert(G->array[dest], source); //CHECK
}



int* SearchEkono(graphList* G, int v, int* Arr, int jona){
    puts("In");
    if (G->array[v]->curr->vis == VISITADO) {
        jona--;     //Comprobar jona en ruteo
        return Arr; //Cachar si es la unica forma u.u
        puts("YaV");
    }

    G->array[v]->curr->vis = VISITADO;

    Arr[jona] = G->array[v]->curr->numbr;

//A -> B -> C -> D -> F
//B -> E -> D
//E -> C
//D -> E -> X
//F -> |_

    while(G->array[v]->curr != G->array[v]->tail){
        jona++;
        next(G->array[v]);
        SearchEkono(G, G->array[v]->curr->numbr, Arr, jona);
    }
    return Arr;
}

linkList* finalArr(int* A, int nodosGrafo, int* B, int alcanzables){

    int i,j;

    linkList* list = ListConstructor();

    for (i = 0; i < nodosGrafo; i++) {

        for (j = 0; j < alcanzables; j++) {

          if(A[i] == B[j]){
              listInsert(list,A[i]);
          }
        }
    }

    return list;
}

void printToScreen(linkList* l){

    printf("%d ", l->size);

    while (l->curr != l->tail) {
        printf("%d ",l->curr->numbr);
        next(l);
    }

    printf("\n");
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
