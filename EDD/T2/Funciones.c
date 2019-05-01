#include <stdio.h>
#include <stdlib.h>

/******
*Definicion tipos de elementos de polinomios
******/
typedef int tElemPoli;

/*****
*Struct monomio de un polinomio
*   coef: valor entero correspondiente al coeficiente
*   expo: valor entero positivo del exponente
*   sig: struct nodo puntero al siguiente nodo
*****/
typedef struct mono{
    tElemPoli coef;
    tElemPoli expo;
    struct mono* sig;
}tmono;

/*****
*Struct Lista enlazada de polinomios
*   head: puntero al nodo inicial de la lista
*   tail: puntero al nodo final de la lista
*   act: puntero en la ubicacion actual de la lista
*   listSize: tamano de la lista
*   pos: index con la posicion actual de la lista
*****/
typedef struct{
    tmono* head;
    tmono* tail;
    tmono* act;
    unsigned int ListSize;
    unsigned int pos;
}tPoli;

/*****
*   tPoli* constLista
******
*   Constructor de la lista, asigna la memoria necesaria a la estructura, inicia la lista con 0 elementos
******
*   Input:
*       Nada
******
*   Returns:
*       tPoli*, lista inicializada
*****/
tPoli* constLista(){
    tPoli *P = (tPoli*)malloc(sizeof(tPoli));
    P->head = P->tail = P->act = NULL;
    P->ListSize = 0;
    P->pos = 0;
    return P;
}

/*****
*   void Next
******
*   Mueve el puntero a la posicion actual de la lista al siguiente elemento
******
*   Input:
*       tPoli* P: Puntero a lista enlazada P
******
*   Returns:
*       Nada
*****/
void Next(tPoli *P){
    if (P->act != P->tail) {
        P->act = P->act->sig;
        P->pos++;
    }
}

/*****
*   tPoli* Prev
******
*   Mueve el puntero con la posicion actual al nodo anteror a esta
******
*   Input:
*       tPoli* P: Puntero a lista enlazada P
******
*   Returns:
*       Nada
*****/
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

/*****
*   void Insert
******
*   Anade un elemento nuevo a la lista, se encarga de crearlo con la informacion solicitada
******
*   Input:
*       tPoli* P: lista de monomios en la cual se agrgara el nuevo elemnto
*       tElemPoli c: un entero con el coeficiente del monomio
*       tElemPoli e: un entero positivo con el exponente del monomio
******
*   Returns:
*       Nada
*****/
void Insert(tPoli* P, tElemPoli c, tElemPoli e){
    if (P->head == NULL){   //en caso que la lista este vacia
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

/*****
*   void Clear
******
*   Limpia la lista, eliminando todos los nodos
******
*   Input:
*       tPoli* P: lista de monomios a la cual se le eliminaran los elementos
******
*   Returns:
*       Nada
*****/
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
/*****
*   void destructorLista
******
*   Libera la memoria de la lista
******
*   Input:
*       tPoli* P: lista de monomios que se desea liberar
******
*   Returns:
*       Nada
*****/
void destructorLista(tPoli* P){
    if(P->head !=NULL) free(P->head);
    free(P);
}
/*****
*   int GetExpo
******
*   Funcion que se encarga de obtener el exponente del nodo de la posicion actual
******
*   Input:
*       tPoli* P: lista de monomios de la cual se quiere obtener el exponente
******
*   Returns:
*       int, exponente de la posicion actual
*****/
int GetExpo(tPoli* P){
    return (int)P->act->expo;
}

/*****
*   int GetCoef
******
*   Funcion que se encarga de obtener el coeficiente del nodo de la posicion actual
******
*   Input:
*       tPoli* P: lista de monomios de la cual se quiere obtener el coeficiente
******
*   Returns:
*       int, coeficiente de la posicion actual
*****/
int GetCoef(tPoli* P){
    return (int)P->act->coef;
}

/*****
*   void MoveToStart
******
*   Mueve el puntero con la posicion actual de la lista al inicio de esta
******
*   Input:
*       tPoli* P: lista de monomios en la cual se quiere mover la posicion
******
*   Returns:
*       Nada
*****/
void MoveToStart(tPoli *P) {
    P->act = P->head;
    P->pos = 0;
}


/*****
*   void MoveToEnd
******
*   Mueve el puntero con la posicion actual de la lista al final de esta
******
*   Input:
*       tPoli* P: lista de monomios en la que se quiere mover la posicion
******
*   Returns:
*       Nada
*****/
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

/*****
*   int Coeficiente
******
*   Obtiene el coefiente de un polinomio de un arreglo de polinomios a partir de su exponente
******
*   Input:
*       tPoli** POLI: arreglo de listas enlazadas
*       int M: cantidad de polinomios
*       int p: polinomio que se desea buscar en el arreglo
*       int e: exponente del monomio que se desea encontrar
*   Returns:
*       int, coeficiente del monomio
*       int, retorna 0 en caso de no haberlo encontrado
*****/
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

/*****
*   int Evaluar
******
*   Calcula el resultado de evaluar un polinomio con un x deseado usando el elgoritmo de horner
******
*   Input:
*       tPoli** POLI: arreglo de listas enlazadas
*       int M: cantidad de polinomios
*       int p: polinomio que se desea buscar en el arreglo
*       float X: variable a evaluar en el polinomio
*       FILE* out: archivo de salida donde se imprimira el resultado
******
*   Returns:
*       Nada
*****/
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
    S = Coeficiente(POLI, M, p, 0) + X*S;   //monomio de exponente 0

//Impresion en archivo
    fprintf(out, "%f\n", S);

    return 0;
}
