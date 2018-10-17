
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
    int i;
    L->curr = L->head = L->tail = (listNode*)generateNode();
    L->curr->next = NULL;
    for (i = 1; i < size; i++) {
        L->tail->next = (listNode*)generateNode();
        L->tail = L->tail->next;
    }
    L->listSize = size;
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

    moveToStart(Lista);

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


void moveToPos(int pos, linkList* List) {
    moveToStart(List);
    while(List->pos != pos){
        next(List);
    }
}


void cruceMedio(void* Lista1, void* Lista2){

    int a = (((linkList*)(Lista1))->listSize)/2-1; //elemento posterior a mitad
    int b = (((linkList*)(Lista2))->listSize)/2-1;

    moveToPos(a,((linkList*)(Lista1)));
    moveToPos(b,((linkList*)(Lista2)));

    listNode* P1 = ((linkList*)Lista1)->curr->next;

    ((linkList*)Lista1)->curr->next = ((linkList*)Lista2)->curr->next;
    ((linkList*)Lista2)->curr->next = P1;

    listNode* H1 = ((linkList*)(Lista1))->head;
    listNode* H2 = ((linkList*)(Lista2))->head;

    ((linkList*)Lista1)->head = H2;
    ((linkList*)Lista2)->head = H1;

    int nSize = (((linkList*)Lista1)->listSize + ((linkList*)Lista2)->listSize)/2;

    ((linkList*)Lista1)->listSize = nSize;
    ((linkList*)Lista2)->listSize = nSize;

    imprimirSolucion(Lista1);
    printf("diferenciar las dos\n");
    imprimirSolucion(Lista2);
};

void mutacionRand(void* Lista){
    char* a[] = {"i","c","b"};
    char* b[] = {"A","B","C","D","E","F"};

    int domo = rand() % ((linkList*)Lista)->listSize;
    moveToPos(domo,((linkList*)Lista));

    ((linkList*)Lista)->curr->type = *a[rand()%3];

    int flag = 1;

    if (((linkList*)Lista)->curr->type == 'i'){
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%10;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (int*)malloc(sizeof(int));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else if (((linkList*)Lista)->curr->type == 'c') {
     	char* data2 = (char*)malloc(sizeof(char));
        while(flag != 0){
            *data2 = *b[rand()%6];
            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (char*)malloc(sizeof(char));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else{
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%2;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (int*)malloc(sizeof(int));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }
}


void mutacionTipo(void* Lista){
    char* b[] = {"A","B","C","D","E","F"};

    int domo = rand() % ((linkList*)Lista)->listSize;
    moveToPos(domo,((linkList*)Lista));

    int flag = 1;

    if (((linkList*)Lista)->curr->type == 'i'){
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%10;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else if (((linkList*)Lista)->curr->type == 'c') {
     	char* data2 = (char*)malloc(sizeof(char));
        while(flag != 0){
            *data2 = *b[rand()%6];
            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else{
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%2;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }
}


void cruceIntercalado(void* Lista1, void* Lista2){










}


int evaluacionLista(int (*fun)(void*), void* Lista);

void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
