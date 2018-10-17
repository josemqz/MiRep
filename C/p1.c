#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000000
//Implementar TDAs (linked en este caso) con funciones correspondientes
//Obtencion de informacion
    //leer archivos
    //verificarlos
    //asegurar ubicacion inicial
    //Crear y asignar memoria a arreglo de listas enlazadas
    //fgetc -> primer caracter ==> cantidad de polinomios a seguir
                                    //(podria haber un while i<P y al final de cada polinomio sumarle 1)
        //fgetc -> cantidad de monomios a seguir (aquí un for (i < cantidad de lineas))
                //scan a struct -> exponente y coeficiente
//Implementacion funciones pedidas

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

void Insert(tPoli* P, tElemPoli c, tElemPoli e){    //pls
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

void Append(tPoli* P, tElemPoli c, tElemPoli e){
    if (P->head == NULL){
        P->act = P->head = P->tail = (tmono*)malloc(sizeof(tmono));
        P->act->coef = c;
        P->act->expo = e;
        P->act->sig = NULL;
    }
    else{
        P->tail->sig = (tmono*)malloc(sizeof(tmono));
        P->tail->sig->coef = c;
        P->tail->sig->expo = e;
        P->tail = P->tail->sig;
    }
    P->ListSize++;
}

void Remove(tPoli* P){      //supuestamente no se usara (esta malo aun)
    if (P->act == P->head){
        P->head = P->act->sig;
        free(P->act);
    }
    else{
        Prev(P);
        P->act->sig = P->act->sig->sig;
        P->act->sig = NULL;
        free(P->act->sig);
    }
    P->ListSize--;
}

void Clear(tPoli* P){
    tmono* curr = P->head;
    tmono* next;
    while(curr != NULL){
        next = curr->sig;
        free(curr);
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

tElemPoli GetExpo(tPoli* P){
    return P->act->expo;
}

tElemPoli GetCoef(tPoli* P){
    return P->act->coef;
}

void MoveToStart(tPoli *P) {
    P->act = P->head;
    P->pos = 0;
}

void MoveToEnd(tPoli* P){
    P->act = P->tail;
    P->pos = P->ListSize-1;
}

//-------------------------------------------
int main(){
    int i,j;
    FILE* fp;

    fp = fopen("in.txt","r");

    //Verify(fp);

    int M;  //cantidad polinomios
    fscanf(fp,"%d", &M);

    //Arreglo con listas enlazadas
    tPoli** PAUL = (tPoli**)malloc(M*sizeof(tPoli*));

    for (i = 0; i < M; i++){
        int N;  //cantidad monomios
        fscanf(fp,"%d", &N);

        #define P PAUL[i]

        P = BobLink();
        for (j = 0; j < N; j++){
            int e,c;
            fscanf(fp,"%d %d\n", &e, &c);
            Insert(P, c, e);
            if(P->act != P->head) Next(P);
            printf("c:%d e:%d\n", GetCoef(P), GetExpo(P));
        }
    }

    for (i = 0; i < M; i++){
        Clear(PAUL[i]);
        RalphLink(PAUL[i]);
    }
    fclose(fp);
    return 0;
}
