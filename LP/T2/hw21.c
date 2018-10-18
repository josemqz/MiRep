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

void MoveToStart(ListGen* L){
    L->curr = L->head;
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

void* getRand(tNodo* node){

    char* a[] = {"i","c","b"};
    char* b[] = {"A","B","C","D","E","F"};

    char i = *a[rand() % 3];
    ((tNodo*)node)->tipo = i;


    if (i == 'i') {
    	int* data2 = (int*)malloc(sizeof(int));
    	*data2 = rand() % 10;
     	((tNodo*)node)->dato = data2;
    }

    else if (i == 'c') {
    	char* data2 = (char*)malloc(sizeof(char));
    	*data2 = *b[rand() % 6];
        ((tNodo*)node)->dato = data2;
    }

    else{
    	int* data2 = (int*)malloc(sizeof(int));
    	*data2 = rand() % 2;
        ((tNodo*)node)->dato = data2;
    }

    return node;
}

void* generarSolucion(int n){

    ListGen* S = (ListGen*) malloc (sizeof(ListGen)); //nueva lista

    S->tail = S->head = S->curr = (tNodo*) malloc (sizeof(tNodo));
    S->tail = S->head = S->curr = (tNodo*)getRand(S->curr);

    int i;
    for (i = 1; i < n; i++){

        S->tail->next = (tNodo*)malloc(sizeof(tNodo));
        S->tail->next = (tNodo*)getRand(S->tail->next);

        //---------------------------------------------
        if (S->tail->next->tipo == 'c'){
            printf("charCOP: %c\n", *((char*) S->tail->next->dato));
        }
    //int
        else if (S->tail->next->tipo == 'i'){
            printf("intCOP: %d\n", *((int*) S->tail->next->dato));
        }
    //bitatom://teletype/portal/be8466f5-bfff-4a51-9560-19afc91dc00d
        else if (S->tail->next->tipo == 'b'){
            printf("bitCOP: %d\n", *((unsigned int*) S->tail->next->dato));
        }
                //-------------------------------------------------
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

    Cop->tail = Cop->head = Cop->curr = (tNodo*) malloc (sizeof(tNodo));
    Cop->tail = Cop->head = Cop->curr = (tNodo*)getRand(Cop->curr);

    MoveToStart((ListGen*)S);

    int i;
    for(i = 1; i < (int)((ListGen*)S)->size; i++){

        Cop->tail->next = (tNodo*)malloc(sizeof(tNodo));

        Cop->tail->next->tipo = ((ListGen*)S)->curr->tipo;    //ERROR
        Cop->tail->next->dato = ((ListGen*)S)->curr->dato;

    //---------------------------------------------
    if (Cop->tail->next->tipo == 'c'){
        printf("charCOP: %c\n", *((char*) Cop->tail->next->dato));
    }
//int
    else if (Cop->tail->next->tipo == 'i'){
        printf("intCOP: %d\n", *((int*) Cop->tail->next->dato));
    }
//bit
    else if (Cop->tail->next->tipo == 'b'){
        printf("bitCOP: %d\n", *((unsigned int*) Cop->tail->next->dato));
    }
            //-------------------------------------------------

        Cop->tail = Cop->tail->next;
        Next((ListGen*)S);
    }

    Cop->size = ((ListGen*)S)->size;

    return Cop;
}


void Clear(void* S){
     tNodo* curr = ((ListGen*)S)->head;
     tNodo* sig;
    while(curr != NULL){
        sig = curr->next;

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

    copiar(S);
    //Clear(S);
    return 0;
}
