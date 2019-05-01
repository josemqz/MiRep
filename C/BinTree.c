#include <stdio.h>
#include <stdlib.h>

typedef int tElemArb;

typedef struct nodo{
    tElemArb item;
    struct nodo* izq;
    struct nodo* der;
}tNodo;

typedef struct{
    tNodo* raiz;
    int nNodos;
}tArbol;

tArbol BobTree(){   //no es necesario si trato al arbol como un struct
    tArbol T;
    T.raiz = NULL;
    T.nNodos = 0;
    return T;
}

void insertHelper(tArbol T, tElemArb x, tNodo* n){
    if (n == NULL) {
        n = (tNodo*)malloc(sizeof(tNodo));
        n->item = x;
        T.nNodos++;
    }
    else if(x < n->item) insertHelper(T, x, n->izq);
    else if(x > n->item) insertHelper(T, x, n->der);
}

void insert(tArbol T, tElemArb x){
    if (T.raiz == NULL) {
        T.raiz = (tNodo*)malloc(sizeof(tNodo));
        T.raiz->item = x;
        T.nNodos++;
    }
    else if(x < T.raiz->item) insertHelper(T, x, T.raiz->izq);
    else if(x > T.raiz->item) insertHelper(T, x, T.raiz->der);
}

/*
tNodo* findHelp(tNodo* n, tElemArb x){
    if (n->item == x) {
        return n;
    }
    else if(x < n->item) findHelp(x, n->izq);
    else if(x > n->item) findHelp(x, n->der);
    else return;//
}

tNodo* findN(tArbol T, tElemArb x){
    return findHelp(T.raiz, x);
 }
*/

void swap(tElemArb x, tNodo* n, tNodo* m){
    tNodo* aux;
    aux = n;
    n = m;
    m = aux;
    free(aux);
}

void removeHelper(tArbol T, tElemArb x, tNodo* n){
    if (x == n->item){
        if (n->izq == NULL && n->der == NULL){  //si es hoja
            free(n);
            T.nNodos--;
        }
        else if (x < n->izq->item) swap(x, n, n->izq);
        else if (x > n->izq->item) swap(x, n, n->der);
    }
    if (x < n->item) removeHelper(T, x, n->izq);
    else if (x > n->item) removeHelper(T, x, n->der);
}

void remove(tArbol T, tElemArb x){
    if (x < T.raiz->item) removeHelper(T, x, T.raiz->izq);
    else if (x > T.raiz->item) removeHelper(T, x, T.raiz->der);
//
}

void clearHelper(tNodo* n){
    if (n == NULL) return;
    clearHelper(n->izq);
    clearHelper(n->der);
    free(n);
}

void clear(tArbol T){
    clearHelper(T.raiz);
    T.nNodos = 0;
}
