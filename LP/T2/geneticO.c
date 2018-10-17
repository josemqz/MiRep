#include "stdio.h"
#include "stdlib.h"
#include "time.h"


typedef struct node{
    void* data;
    char type; // "i","c","b"
    struct node* next;
}listNode;

typedef struct {
    listNode* head;
    listNode* tail;
    listNode* curr;
    int listSize;
    int pos;
}linkList;

void* getRand(listNode* node){

    char* a[] = {"i","c","b"};
    char* b[] = {"A","B","C","D","E","F"};

    char i = *a[rand() % 3];
    ((listNode *)node)->type = i;


    if (i== 'i') {
    	int* data2 = (int*)malloc(sizeof(int));
    	*data2 = rand() % 10;
     	((listNode*)node)->data = data2;
    }
    else if (i == 'c') {
    	char* data2 = (char*)malloc(sizeof(char));
    	*data2 = *b[rand() % 6];
     	((listNode*)node)->data = data2;
    }
    else{
     	int* data2 = (int*)malloc(sizeof(int));
    	*data2 = rand() % 2;
        ((listNode*)node)->data = data2;
     	}
    return node;
}


//a=rand%10
//b=malloc
//*((int*)b)
void* generateNode(){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node = (listNode*)getRand(node);
    return node;
}
void next(void* List) {
    if (((linkList*)(List))->curr != ((linkList*)(List))->tail) {
        ((linkList*)(List))->curr = ((linkList*)(List))->curr->next;
        ((linkList*)(List))->pos++;
    }
}

void* generarSolucion(int largo){
    linkList* L = (linkList*)malloc(largo*sizeof(linkList));
    int i;
    L->curr = L->head = L->tail = (listNode*)generateNode();
    L->curr->next = NULL;
    for (i = 1; i < largo; i++) {
        L->tail->next = (listNode*)generateNode();
        L->tail = L->tail->next;
    }
    L->listSize = largo;
    return L;
}

int getSize(void* List){
    return ((linkList*)(List))->listSize;
}
void moveToStart(void* List){
    ((linkList*)(List))->curr = ((linkList*)(List))->head;
    ((linkList*)(List))->pos = 0;

}

void* copiar(void* Lista){
    int size = ((linkList*)Lista)->listSize;
    linkList *L = (linkList*)malloc(size*sizeof(linkList));
    L->curr = L->head = L->tail = (listNode*)malloc(sizeof(listNode));
    int i;
    for (i = 0; i < ((linkList*)Lista)->listSize ;i++ ) {
        L->curr = ((linkList*)Lista)->curr;
    }
    return L;
}

void borrar(void* Lista){
    listNode* node = ((linkList*)Lista)->head;
    listNode* nxt;
    while (node != NULL) {
        nxt = node->next;
        free(node->data);
        free(node);
        node = nxt;
    }
    ((linkList*)Lista)->head = NULL;
    ((linkList*)Lista)->listSize = 0;
    free(((linkList*)(Lista)));
}



void imprimirSolucion(void* Lista) {
int i;
    for (i = 0; i<((linkList*)(Lista))->listSize; i++) {

         if (((linkList*)(Lista))->curr->type == 'c') {
            printf("data:%c\ttype:%c\n",  *((char*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }
        else{
            printf("data:%d\ttype:%c\n", *((int*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }
        next((linkList*) Lista);
    }

}

void cruceMedio(void* Lista1, void* Lista2);

void cruceIntercalado(void* Lista1, void* Lista2);

void mutacionRand(void* Lista);

void mutacionTipo(void* Lista);

int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
