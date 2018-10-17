#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000000

typedef int tElemLista;

typedef struct{
    unsigned int ArSize;    //tamanio maximo arreglo
    unsigned int ListSize;  //tamanio de la lista en si
    unsigned int curr;
    tElemLista *ArList;
}tLista;

tLista* BobLista(){ //el constructor
    tLista *L1 = (tLista*)malloc(sizeof(tLista));
    L1->ArSize = MAXSIZE;
    L1->ListSize = 0;
    L1->curr = 0;
    L1->ArList = (tElemLista *)malloc(MAXSIZE*sizeof(tElemLista));
    return L1;
}

void Clear(tLista* L){
    free((void*)L->ArList);
    L->ListSize = L->curr = 0;
    L->ArList = (tElemLista *)malloc(L->ArSize * sizeof(tElemLista));
}

int Insert(tLista* L, tElemLista x){
    if(L->ListSize >= L->ArSize) return -1; //lleno
    unsigned int i;
    for(i = L->ListSize; i > L->curr; i--){
        L->ArList[i] = L->ArList[i-1];
    }
    L->ArList[i] = x;
    L->ListSize++;
    return 0; //supuestamente deberia retornar la posicion i. nieh
}

tElemLista Remove(tLista* L){ //y retornar valor
    if (L->curr < 0 || L->curr >= L->ListSize) return -1; //no necesariamente tElemLista :s
    unsigned int i;
    tElemLista a = L->ArList[L->curr];
    for(i = L->curr; i < L->ListSize-1; i++){
        L->ArList[i] = L->ArList[i+1];
    }
    L->ListSize--;
    return a;
}

int Append(tLista* L, tElemLista x){
    if(L->ListSize >= L->ArSize) return -1;
    L->ArList[L->ListSize++] = x; //++?
    L->ListSize++;
    return 0;
}

int Prev(tLista* L){
    if (L->curr != 0){
        L->curr--;
        return 0;
    }
}

int Next(tLista* L){
    if (L->curr != L->ListSize-1) {
        L->curr++;
        return 0;
    }
}

void MoveToStart(tLista* L){
    L->curr = 0;
}

void MoveToEnd(tLista* L){
    L->curr = L->ListSize-1;
}

void RalphLista(tLista* L){
    free((void*)L->ArList);
    free(L);
}

int Length(tLista* L){
    return L->ListSize;
}

int MoveToPos(tLista* L, unsigned int x){
    if (x >= L->ListSize) return -1;
    L->curr = x;
    return 0;
}

int CurrPos(tLista* L){
    return L->curr;
}

tElemLista GetValue(tLista* L){
    return L->ArList[L->curr];
}

//-----------------------------------------------------------

int main(){//RECUERDA INVOCAR AL DESTRUCTOR ANTES DE TERMINAR
    tLista *L = BobLista();
    printf("%d\n", Length(L));
    Insert(L,3);
    Insert(L,53);
    Insert(L,5);
    printf("%d\n", Length(L));
    Next(L);
    printf("curr: %d\n", CurrPos(L));
    Prev(L);
    printf("curr: %d\n", CurrPos(L));
    MoveToEnd(L);
    printf("curr: %d\n", CurrPos(L));
    RalphLista(L);
    return 0;
}
