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


tPoli* constLista(){
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

void destructorLista(tPoli* P){
    if(P->head !=NULL) free(P->head);
    free(P);
}

/*unsigned int CurrPos(tPoli* P){
    return P->pos;
}*/

/*int Length(tPoli* P){
    return P->ListSize;
}*/

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

int Coeficiente(tPoli** POLI, int M, int p, int e){
    if (p < M){
        MoveToStart(POLI[p]);
        while(e != POLI[p]->act->expo){
            if (POLI[p]->act == POLI[p]->tail){
                return 0;
            }
            Next(POLI[p]);
        }
        return GetCoef(POLI[p]);
    }
    else{
        return 0;
    }
}

int Evaluar(tPoli** POLI, int M, int p,float X, FILE* out){
    unsigned int i, j;
    int MaxCoef, MaxExpo = 0;
    float S;

//Obtencion de maximo exponente
    MoveToStart(POLI[p]);
    for (i = 0; i < POLI[p]->ListSize; i++){
        if (POLI[p]->act->expo > MaxExpo) MaxExpo = POLI[p]->act->expo;
        Next(POLI[p]);
    }
//Coeficiente de monomio de maximo exponente
    MaxCoef = Coeficiente(POLI, M, p, MaxExpo);

//ALGORITMO DE HORNER
    S = (float)MaxCoef;
    j = MaxExpo-1;  //contador
    while(j > 0){
        S = Coeficiente(POLI, M, p, j) + X*S;
        j--;
    }
    S = Coeficiente(POLI, M, p, 0) + X*S;

//Impresion en archivo
    fprintf(out, "%f\n", S);

    //printf("%f\n",S);
    return 0;
}
