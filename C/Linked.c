#include <stdio.h>
#include <stdlib.h>

//enlazada: lista cuyos elementos se relacionan a traves de punteros

typedef int tElemLink;

typedef struct nodo{    //cada nodo
    tElemLink elem;
    struct nodo* sig;
}tNodo;

typedef struct{     //la lista compuesta por nodos
    tNodo* head;
    tNodo* tail;
    tNodo* act;
    unsigned int ListSize;
    unsigned int pos;
}tLista;


tLista* BobLink(){
    tLista *L = (tLista*)malloc(sizeof(tLista));
    L->head = L->tail = L->act = NULL;
    L->ListSize = 0;
    L->pos = 0;
    return L;
}

void Next(tLista *L){
    if (L->act != L->tail) {
        L->act = L->act->sig;
        L->pos++;
    }
}

void Prev(tLista* L){
    if (L->act != L->head){
        tNodo* aux = L->act;
        L->act = L->head;
        while(L->act->sig != aux){
            Next(L);
            L->pos--;
        }
        L->pos--;
    }
}

void Insert(tLista* L, tElemLink x){
    if (L->head == NULL){ //lista vacia
        puts("Primer insert");
        L->act = L->head = L->tail = (tNodo*)malloc(sizeof(tNodo));
        L->act->elem = x;
    }
    else {
        puts("Insert medio");
        tNodo* aux = L->act->sig; //se crea un auxiliar para no perder el puntero al siguiente nodo (y por consiguiente, a todos los demás nodos de la lista)
        L->act->sig = (tNodo*)malloc(sizeof(tNodo)); //memoria al siguiente
        L->act->sig->elem = x;
        if (L->tail == L->act){
            L->act->sig->sig = NULL;
            L->tail = L->act->sig;
        }
        else L->act->sig->sig = aux;
    }
    L->ListSize++;
}

void Append(tLista* L, tElemLink x){
    if (L->head == NULL){
        L->act = L->head = L->tail = (tNodo*)malloc(sizeof(tNodo));
        L->act->elem = x;
        L->act->sig = NULL;
    }
    else{
        L->tail->sig = (tNodo*)malloc(sizeof(tNodo));
        L->tail->sig->elem = x;
        L->tail = L->tail->sig;
    }
    L->ListSize++;
}

void Remove(tLista* L){
    if (L->act == L->head){
        free(L->head);
        L->act = L->head = L->act->sig;
    }
    else{
        Prev(L);
        tNodo* aux;
        aux = L->act->sig->sig;
        free(L->act->sig);
        L->act->sig = aux;
    }
    L->ListSize--;
}

void Clear(tLista* L){
    tNodo* curr = L->head;
    tNodo* next;
    while(curr != NULL){
        next = curr->sig;
        free(curr);
        curr = next;
    }
    L->head = NULL;
    L->ListSize = 0;
    L->pos = 0;
}

void RalphLink(tLista* L){
    if(L->head !=NULL) free(L->head);
    free(L);
}

unsigned int CurrPos(tLista* L){
    return L->pos;
}

int Length(tLista* L){
    return L->ListSize;
}

tElemLink GetValue(tLista* L){
    return L->act->elem;
}

void MoveToStart(tLista *L) {
    L->act = L->head;
    L->pos = 0;
}

void MoveToEnd(tLista* L){
    L->act = L->tail;
    L->pos = L->ListSize-1;
}


/*  PRUEBAS
int main(){
    tLista* L = BobLink();
    Insert(L,80);

    printf("p:%d\n", CurrPos(L));
    printf("v:%d\n", GetValue(L));

    Insert(L,10);
    Insert(L,15);

    Next(L);
    printf("l:%d\n", Length(L));
    printf("p:%d\n", CurrPos(L));

    Append(L,56);   //80,15,10,56
    MoveToEnd(L);
    Prev(L);

    Insert(L,4); //80,15,10,4,56
    Next(L);
    Remove(L);
    printf("p:%d\n", CurrPos(L));
    printf("v:%d\n", GetValue(L));

    Insert(L,4895); //80,15,10,4895,56
    printf("tail:%d\n", L->tail->elem);

    for (MoveToStart(L); L->act->sig != NULL; Next(L)) {
        printf("%d\n",GetValue(L));
    }

    printf("%d\n",GetValue(L));
    MoveToEnd(L);
    printf("pos: %d\n", CurrPos(L));

    Clear(L);
    RalphLink(L);
    return 0;
}
*/
