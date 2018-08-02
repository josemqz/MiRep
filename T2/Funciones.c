#include <stdio.h>
#include <stdlib.h>

typedef int tElemPoli;

typedef struct mono{
    tElemPoli coef;
    tElemPoli expo;
    struct mono* sig;
}tmono;

typedef struct{
    tmono* head;
    tmono* tail;
    tmono* act;
    unsigned int ListSize;
    unsigned int pos;
}tPoli;


tPoli* BobLink(){
    tPoli *P = (tPoli*)malloc(sizeof(tPoli));
    P->head = P->tail = P->act = NULL;
    P->ListSize = 0;
    P->pos = 0;
    return P;
}

void Next(tPoli *P){
    if (P->act != P->tail) {
        P->act = P->act->sig;
        P->pos++;
    }
}

void Prev(tPoli* P){
    if (P->act != P->head){
        tmono* aux = P->act;
        P->act = P->head;
        while(P->act->sig != aux){
            Next(P);
            P->pos--;
        }
        P->pos--;
    }
}

void Insert(tPoli* P, tElemPoli c, tElemPoli e){
    if (P->head == NULL){ //lista vacia
        P->act = P->head = P->tail = (tmono*)malloc(sizeof(tmono));
        P->act->coef = c;
        P->act->expo = e;
    }
    else {
        tmono* aux = P->act->sig;
        P->act->sig = (tmono*)malloc(sizeof(tmono));
        P->act->sig->coef = c;
        P->act->sig->expo = e;
        if (P->tail == P->act){
            P->act->sig->sig = NULL;
            P->tail = P->act->sig;
        }
        else P->act->sig->sig = aux;
    }
    P->ListSize++;
}

void Clear(tPoli* P){
    tmono* curr = P->head;
    tmono* next;
    while(curr != NULL){
        next = curr->sig;
        free(curr);     //valgrind webea >:c
        curr = next;
    }
    P->head = NULL;
    P->ListSize = 0;
    P->pos = 0;
}

void RalphLink(tPoli* P){
    if(P->head !=NULL) free(P->head);
    free(P);
}

unsigned int CurrPos(tPoli* P){
    return P->pos;
}

int Length(tPoli* P){
    return P->ListSize;
}

int GetExpo(tPoli* P){
    return (int)P->act->expo;
}

int GetCoef(tPoli* P){
    return (int)P->act->coef;
}

void MoveToStart(tPoli *P) {
    P->act = P->head;
    P->pos = 0;
}

void MoveToEnd(tPoli* P){
    P->act = P->tail;
    P->pos = P->ListSize-1;
}


/*****
*   int verify
******
*   Funcion que verifica la correcta apertura de un archivo.
******
*   Input:
*       FILE *a : variable que apunta a un archivo
*       char *b : nombre del archivo
*        ......
******
*   Returns:
*       int, si el archivo no está vacío retorna el valor 0
*       NULL, se retorna en caso de fallar
*****/
int verify (FILE *a, const char *b){
    if( a == NULL){
        printf("Archivo %s no pudo abrirse.\n", b);
        exit(1);
    }
    return 0;
}

int Coeficiente(tPoli** PAUL, int M, int p, int e){
    if (p < M){
        MoveToStart(PAUL[p]);
        while(e != PAUL[p]->act->expo){
            if (PAUL[p]->act == PAUL[p]->tail){
                return 0;
            }
            Next(PAUL[p]);
        }
        return GetCoef(PAUL[p]);
    }
    else{
        return 0;
    }
}

/*tElemPoli* Ordenar(tElemPoli* P){
    int MaxExpo = 0;
    int i,j;
    for(i = 0; i < ListSize(P); i++){
        for(j = 0; j < )
}
}?*/

int Evaluar(tPoli** PAUL, int M, int p,int X, FILE* in, FILE* out){
    unsigned int i, j;
    int MaxExpo = 0;
    int MayCoef;
    float S;

    for (i = 0; i < PAUL[p]->ListSize; i++){
        if (PAUL[p]->act->expo > MaxExpo) MaxExpo = PAUL[p]->act->expo;
    }

    MayCoef = Coeficiente(PAUL, M, p, MaxExpo);
    S = PAUL[p]->act->expo + MayCoef * X;
    for (j = MaxExpo-1; j >= 0; j--){
        if ((unsigned int)PAUL[p]->act->expo == j){
            S = GetCoef() + MayCoef * X;
            //S = S GetCoef(PAUL[p]) + X * ;
        }
    }
    return 0;
}
