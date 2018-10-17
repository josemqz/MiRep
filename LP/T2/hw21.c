#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tNodo{
    void* dato;
    char tipo; // 'i', 'c', 'b'
    struct tNodo* next;
}tNodo;

typedef struct{
    struct tNodo* head;
    struct tNodo* curr;
    struct tNodo* tail;
    unsigned int size;
}ListGen;


void Next(ListGen* L){
    L->curr = L->curr->next;
}

void RandNodo(struct tNodo* N){
    //definir aleatoriamente tipo de dato del nodo actual
        N->tipo = "cib"[rand() % 3];
        //S->curr->tipo = 'i';

    //char
        if (N->tipo == 'c'){
            char x;
            x = "ABCDEF"[rand()%6];

            N->dato = &x;
            printf("char: %c\n", *((char*)(N->dato)));
        }

    //int
        else if (N->tipo == 'i'){
            unsigned int y;
            y = rand()%10;

            N->dato = &y;
            printf("int: %d\n", *((unsigned int*) (N->dato)));
        }

    //bit
        else if (N->tipo == 'b'){
            unsigned int z;
            z = rand()%2;

            N->dato = &z;
            printf("bit: %d\n", *((unsigned int*) (N->dato)));
        }
}


void* generarSolucion(int n){

    ListGen* S = (ListGen*) malloc (sizeof(ListGen)); //nueva lista

    S->tail = S->head = S->curr = (tNodo*) malloc (sizeof (tNodo));
    RandNodo (S->curr);

    //char
    if (S->head->tipo == 'c'){
        printf("charhead: %c\n", *((char*) (S->head->dato)));
    }
    //int
    else if (S->head->tipo == 'i'){
        printf("inthead: %d\n", *((int*) (S->head->dato)));
    }
    //bit
    else if (S->head->tipo == 'b'){
        printf("bithead: %d\n", *((unsigned int*) (S->head->dato)));
    }
    //---------------------------------------------
    int i;
    for (i = 1; i < n; i++){

        S->tail->next = (tNodo*) malloc (sizeof (tNodo));
        RandNodo(S->tail->next);

            if(S->tail->next != NULL) S->tail = S->tail->next;
    }

//largo lista
    S->size = n;

    return S;
}


//void∗ copiar(void∗ Lista): crea una copia de la lista ingresada y retorna el puntero
//correspondiente
void* copiar(void* S){

    ListGen *Cop;

    Cop = (ListGen*)malloc(sizeof(ListGen));

    int t;
    t = (int)((ListGen*)S)->size;
    //printf("T:%d\n", t);
    int i;
    ((ListGen*)S)->curr = ((ListGen*)S)->head;

    for(i = 0; i < t-2; i++){

        Cop->curr = ( tNodo*)malloc(sizeof( tNodo));

        if (i == 0){
            Cop->head = Cop->curr;
        }

        Cop->curr->tipo = ((ListGen*)S)->curr->tipo;    //ERROR
        Cop->curr->dato = ((ListGen*)S)->curr->dato;

/*    //---------------------------------------------
    if (Cop->curr->tipo == 'c'){
        printf("char: %c\n", (char*) Cop->curr->dato);
    }
//int
    else if (Cop->curr->tipo == 'i'){
        printf("int: %d\n", (int*) Cop->curr->dato);
    }
//bit
    else if (Cop->curr->tipo == 'b'){
        printf("bit: %d\n", (unsigned int*) Cop->curr->dato);
    }
            //-------------------------------------------------
*/
        Cop->curr = Cop->curr->next;
        ((ListGen*)S)->curr = ((ListGen*)S)->curr->next; //ERROR
    }
    Cop->tail = Cop->curr;
    Cop->size = ((ListGen*)S)->size;

    return Cop;
}


void Clear(void* S){
     tNodo* curr = ((ListGen*)S)->head;
     tNodo* sig;
    printf("1: %c\n", curr->tipo);
    if ( ((ListGen*)S)->head->next == NULL) puts("weaSDKLFJSDHSDFKLDKLAF");
    //printf("2: %c\n", curr->next->tipo);
    while(curr != NULL){
        //puts("AAHAHEFSKDSDFHJ");
        sig = curr->next;
/*
        //char
        if (sig->tipo == 'c'){
            printf("CLEAR:char: %c\n", *((char*) (sig->dato)));
        }
        //int
        else if (sig->tipo == 'i'){
            printf("CLEAR:int: %d\n", *((int*) (sig->dato)));
        }
        //bit
        else if (sig->tipo == 'b'){
            printf("CLEAR:bit: %d\n", *((unsigned int*) (sig->dato)));
        }
*/
        free(curr);
        curr = sig;
    }
    ((ListGen*)S)->head = NULL;
    ((ListGen*)S)->size = 0;
    free(S);
}

/*void RalphLink(tLista* L){
    if(L->head !=NULL) free(L->head);
    free(L);
}*/

int main(){

    time_t now;
    struct tm *tn;
    now = time(NULL);
    tn = localtime(&now);

    srand(tn->tm_sec + tn->tm_min);

    /*int i;
    for(i = 0; i < 10; i++){
        printf("%d\n", rand()%9);
    }*/

    ListGen* S;
    S = (ListGen*)generarSolucion(10);

    if (S->head->tipo == 'c'){
        printf("charhead: %c\n", *((char*) (S->head->dato)));
    }
//int
    else if (S->head->tipo == 'i'){
        printf("inthead: %d\n", *((int*) (S->head->dato)));
    }
//bit
    else if (S->head->tipo == 'b'){
        printf("bithead: %d\n", *((unsigned int*) (S->head->dato)));
    }
    //---------------------------------------------
    if (S->tail->tipo == 'c'){
        printf("chart: %c\n", *((char*)(S->tail->dato)));
    }

    //int
    else if (S->tail->tipo == 'i'){
        printf("intt: %d\n", *((unsigned int*) (S->tail->dato)));
    }

    //bit
    else if (S->tail->tipo == 'b'){
        printf("bitt: %d\n", *((unsigned int*) (S->tail->dato)));
    }

    //-------------------------------------------------

    //1copiar(S);
    //Clear(S);
    return 0;
}
