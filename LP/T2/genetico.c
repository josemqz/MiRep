#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "linkedList.h"
#include "genetico.h"
#include "fun.h"


/*****
*   void* generarSolucion
******
*   Inicializa una lista enlazada y agrega elementos aleatorios de tipo entero, caracter o bit, elegidos al azar
******
*   Input:
*       int largo: largo de lista
******
*   Retorno:
*       void*: Lista enlazada de largo "largo"
*****/
void* generarSolucion(int largo){

//inicializacion lista
    linkList* L = (linkList*)malloc(largo*sizeof(linkList));
    L->curr = L->head = L->tail = (listNode*)generateNode();
    L->curr->next = NULL;

//inicializacion de nodos consecutivos
    int i;
    for (i = 1; i < largo; i++) {
        L->tail->next = (listNode*)generateNode();
        L->tail = L->tail->next;
    }

    L->listSize = largo;
    return L;
}

/*****
*   void* copiar
******
*   Genera una copia de una lista enlaada
******
*   Input:
*       void* S: Lista enlazada a copiar
******
*   Retorno:
*       void*: Lista enlazada, copia de "S"
*****/
void* copiar(void* S){

//inicializacion de nueva lista
    linkList *Cop;
    Cop = (linkList*)malloc(sizeof(linkList));

//inicializacion de primer nodo: copia del primer nodo de S

    Cop->tail = Cop->head = Cop->curr = (listNode*) malloc (sizeof(listNode));

    Cop->tail->type = Cop->head->type = Cop->curr->type = ((linkList*)(S))->head->type;     //asignacion del tipo de dato

//int
    if (((linkList*)(S))->head->type == 'i') {
        int* data2 = (int*)malloc(sizeof(int));
        *data2 = *(int*)(((linkList*)(S))->head->data);
        Cop->tail->data = Cop->head->data = Cop->curr->data = data2;
    }

//char
    else if (((linkList*)(S))->head->type == 'c') {
        char* data2 = (char*)malloc(sizeof(char));
        *data2 = *(char*)(((linkList*)(S))->head->data);
        Cop->tail->data = Cop->head->data = Cop->curr->data = data2;
    }

//bit
    else{
        int* data2 = (int*)malloc(sizeof(int));
        *data2 = *(int*)(((linkList*)(S))->head->data);
        Cop->tail->data = Cop->head->data = Cop->curr->data = data2;
    }

//inicializacion de nodos consecutivos: copias de nodos de S

    moveToStart((linkList*)S);
    next((linkList*)S);

    int i;
    for(i = 1; i < (int)((linkList*)S)->listSize; i++){

        Cop->tail->next = (listNode*)malloc(sizeof(listNode));

        Cop->tail->next->type = ((linkList*)S)->curr->type;         //asignacion del tipo de dato

    //int
        if (((linkList*)(S))->curr->type == 'i') {
            int* data2 = (int*)malloc(sizeof(int));
            *data2 = *(int*)(((linkList*)(S))->curr->data);
            Cop->tail->next->data = data2;
        }

    //char
        else if (((linkList*)(S))->curr->type == 'c') {
            char* data2 = (char*)malloc(sizeof(char));
            *data2 = *(char*)(((linkList*)(S))->curr->data);
            Cop->tail->next->data = data2;
        }

    //bit
        else{
            int* data2 = (int*)malloc(sizeof(int));
            *data2 = *(int*)(((linkList*)(S))->curr->data);
            Cop->tail->next->data = data2;
        }

    //siguiente nodo
        Cop->tail = Cop->tail->next;
        next((linkList*)S);
    }

    Cop->listSize = ((linkList*)S)->listSize;

    return Cop;
}

/*****
*   void borrar
******
*   Elimina una lista enlazada por completo
******
*   Input:
*       void* Lista: Lista enlazada a borrar
******
*   Retorno:
*       Nada
*****/
void borrar(void* Lista){

//variables auxiliares
    listNode* node = ((linkList*)Lista)->head;
    listNode* nxt;

    int i = 0;
    while( i++ < ((linkList*)Lista)->listSize ){

        nxt = node->next;

        free(node->data);
        free(node);

        node = nxt;
    }

    ((linkList*)Lista)->listSize = 0;
    free(((linkList*)(Lista)));
}

/*****
*   void imprimirSolucion
******
*   Imprime el tipo y el dato de cada nodo de una lista enlazada
******
*   Input:
*       void* Lista: Lista enlazada cuyos elementos serán impresos
******
*   Retorno:
*       Nada
*****/
void imprimirSolucion(void* Lista) {

    moveToStart(Lista);

    int i;
    for (i = 0; i < ((linkList*)(Lista))->listSize; i++) {
    //char
         if (((linkList*)(Lista))->curr->type == 'c') {
            printf("(%c,%c)", *((char*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }
    //int - bit
        else{
            printf("(%d,%c)", *((int*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }

        next((linkList*) Lista);
    }

    puts("\n");
}


/*****
*   void cruceMedio
******
*   Intercambia los elementos de la primera mitad de dos listas entre sí
******
*   Input:
*       void* Lista1: Lista enlazada
*       void* Lista2: Lista enlazada
******
*   Retorno:
*       Nada
*****/
void cruceMedio(void* Lista1, void* Lista2){

//se ubica el nodo actual en la posicion anterior a la mitad de la lista

    int a = (((linkList*)(Lista1))->listSize)/2-1;
    int b = (((linkList*)(Lista2))->listSize)/2-1;

    moveToPos(a,((linkList*)(Lista1)));
    moveToPos(b,((linkList*)(Lista2)));

    listNode* P1 = ((linkList*)Lista1)->curr->next;     //puntero auxiliar a nodo posterior a mitad

//intercambio de segunda mitad de lista
    ((linkList*)Lista1)->curr->next = ((linkList*)Lista2)->curr->next;
    ((linkList*)Lista2)->curr->next = P1;

//puntero auxiliar a nodo cabecera
    listNode* H1 = ((linkList*)(Lista1))->head;
    listNode* H2 = ((linkList*)(Lista2))->head;

//intercambio entre listas
    ((linkList*)Lista1)->head = H2;
    ((linkList*)Lista2)->head = H1;

//nuevo tamaño de listas
    int nSize = (((linkList*)Lista1)->listSize + ((linkList*)Lista2)->listSize)/2;

    ((linkList*)Lista1)->listSize = nSize;
    ((linkList*)Lista2)->listSize = nSize;

}

/*****
*   void cruceIntercalado
******
*   Intercambia los elementos de las posiciones pares de dos listas enlazadas entre sí
******
*   Input:
*       void* Lista1: Lista enlazada
*       void* Lista2: Lista enlazada
******
*   Retorno:
*       Nada
*****/
void cruceIntercalado(void* Lista1, void* Lista2){

    moveToStart(((linkList*)Lista1));
    moveToStart(((linkList*)Lista2));

//nodos auxiliares
    listNode* p1;
    listNode* p2;

    listNode* H1 = ((linkList*)Lista1)->head;
    listNode* H2 = ((linkList*)Lista2)->head;

    int i = 0;
    while( i++ < ((linkList*)Lista1)->listSize ) {

//se guardan los nodos siguientes
        p1 = ((linkList*)Lista1)->curr->next;
        p2 = ((linkList*)Lista2)->curr->next;

//intercambio de nodos
        ((linkList*)Lista1)->curr->next = p2;
        ((linkList*)Lista2)->curr->next = p1;

        next(((linkList*)Lista1));
        next(((linkList*)Lista2));
    }
    ((linkList*)Lista2)->head = H1;
    ((linkList*)Lista1)->head = H2;

}

/*****
*   void mutacionRand
******
*   Cambia un elemento escogido al azar de una lista enlazada por uno nuevo que puede ser de cualquier tipo
******
*   Input:
*       void* Lista: Lista enlazada a mutar
******
*   Retorno:
*       Nada
*****/
void mutacionRand(void* Lista){

    char* a[] = {"i","c","b"};
    char* b[] = {"A","B","C","D","E","F"};

    int domo = rand() % ((linkList*)Lista)->listSize;   //domo: posicion aleatoria
    moveToPos(domo,((linkList*)Lista));                 //se mueve la posicion actual a esta

    ((linkList*)Lista)->curr->type = *a[rand()%3];      //tipo aleatorio

    int flag = 1;

//int
    if (((linkList*)Lista)->curr->type == 'i'){

        int* data2 = (int*)malloc(sizeof(int));      //asignacion de memoria a puntero de tipo entero

        while(flag != 0){

            *data2 = rand()%10;                      //elemento aleatorio

            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {    //elemento debe ser distinto al original

            //reemplazo de elemento
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }

//char
    else if (((linkList*)Lista)->curr->type == 'c') {

     	char* data2 = (char*)malloc(sizeof(char));   //asignacion de memoria a puntero de tipo caracter

        while(flag != 0){

            *data2 = *b[rand()%6];                   //elemento aleatorio

            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {   //elemento debe ser distinto al original

            //reemplazo de elemento
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }

//bit
    else{

        int* data2 = (int*)malloc(sizeof(int));     //asignacion de memoria a puntero de tipo entero

        while(flag != 0){

            *data2 = rand()%2;                      //elemento aleatorio

            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {    //elemento debe ser distinto al original

            //reemplazo de elemento
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }
}

/*****
*   void mutacionTipo
******
*   Cambia un elemento escogido al azar de una lista enlazada por uno del mismo tipo
******
*   Input:
*       void* Lista: Lista enlazada a mutar
******
*   Retorno:
*       Nada
*****/
void mutacionTipo(void* Lista){

    char* b[] = {"A","B","C","D","E","F"};

    int domo = rand() % ((linkList*)Lista)->listSize;
    moveToPos(domo,((linkList*)Lista));

    int flag = 1;

//int
    if (((linkList*)Lista)->curr->type == 'i'){

        int* data2 = (int*)malloc(sizeof(int));

        while(flag != 0){

            *data2 = rand()%10;

            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {

                free((((linkList*)Lista)->curr->data));
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }

//char
    else if (((linkList*)Lista)->curr->type == 'c') {

     	char* data2 = (char*)malloc(sizeof(char));

        while(flag != 0){

            *data2 = *b[rand()%6];

            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {

                free((((linkList*)Lista)->curr->data));
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }

//bit
    else{

        int* data2 = (int*)malloc(sizeof(int));

        while(flag != 0){

            *data2 = rand()%2;

            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {

                free((((linkList*)Lista)->curr->data));
                ((linkList*)Lista)->curr->data = data2;

                flag = 0;
            }
        }
    }
}

/*****
*   void evaluacionLista
******
*   Aplica una funcion que evalua cada nodo, y retorna la sumatoria de los puntajes
******
*   Input:
*       int (*fun)(void*): Funcion de evaluacion
*       void* Lista: Lista enlazada a evaluar
******
*   Retorno:
*       int: Evaluacion total de la lista enlazada
*****/
int evaluacionLista(int (*fun)(void*), void* Lista){

    int i, score = 0;
    moveToStart(Lista);

    for ( i = 0; i < ((linkList*)(Lista))->listSize ; i++) {
        score = score + (*fun)(((linkList*)(Lista))->curr);
        next((linkList*)(Lista));
    }

    return score;
}

/*****
*   void genetico
******
*   Se crean dos listas enlazadas de elementos aleatorios, las que son evaluadas.
*   Luego, se aplica un cruce entre ellas, generando dos listas nuevas, las que
*   reemplazarán a las originales en caso de ambas tener una mayor mayor puntuación.
*   Después de esto, se aplica una mutación a las nuevas listas y se evalúan.
*   Si una de ellas supera a su homóloga original, reemplaza a esta.
*   Todo esto se repite una cantidad dada de veces.
******
*   Input:
*       void (*muta)(void*): Función de mutación de listas enlazadas
*       void (*cruce)(void*,void*): Función de cruce entre listas enlazadas
*       int n: Largo de listas
*       int iteraciones: Cantidad de veces a repetir las operaciones
******
*   Retorno:
*       Nada
*****/
void genetico(void (*muta)(void*), void (*cruce)(void*, void*), int n, int iteraciones){

//listas padres
    linkList* S1;
    linkList* S2;
    S1 = (linkList*)generarSolucion(n);
    S2 = (linkList*)generarSolucion(n);

//listas hijas
    linkList* Mejor1;
    linkList* Mejor2;
    Mejor1 = (linkList*)copiar(S1);
    Mejor2 = (linkList*)copiar(S2);

//puntajes padres
    int Score1, Score2;
    Score1 = evaluacionLista(fun, S1);
    Score2 = evaluacionLista(fun, S2);

//impresion listas y puntajes iniciales
    puts("Lista 1 inicial\n");
    imprimirSolucion(S1);
    printf("puntaje lista1 inicial:%d\n", Score1);
    puts("Lista 2 inicial\n");
    imprimirSolucion(S2);
    printf("puntaje lista2 inicial:%d\n", Score2);

    int i = 0;
    while (i < iteraciones){
    //puntajes hijas
        int Score3, Score4;

    //funcion cruce entre listas
        (*cruce)(Mejor1, Mejor2);

        Score3 = evaluacionLista(fun, Mejor1);
        Score4 = evaluacionLista(fun, Mejor2);

    //reemplazo hijas - padres
        if (Score3 > Score1 && Score4 > Score2){
            borrar(S1);
            borrar(S2);
            S1 = Mejor1;
            S2 = Mejor2;
            Score1 = Score3;
            Score2 = Score4;

            Mejor1 = (linkList*)copiar(S1);
            Mejor2 = (linkList*)copiar(S2);
        }

    //funcion mutacion
        (*muta)(Mejor1);
        (*muta)(Mejor2);

        Score3 = evaluacionLista(fun, Mejor1);
        Score4 = evaluacionLista(fun, Mejor2);

    //reemplazos hijas - padres
        if (Score3 > Score1){
            borrar(S1);
            S1 = Mejor1;
            Score1 = Score3;

            Mejor1 = (linkList*)copiar(S1);
        }
        if (Score4 > Score2){
            borrar(S2);
            S2 = Mejor2;
            Score2 = Score4;

            Mejor2 = (linkList*)copiar(S2);
        }

        i++;
    }

//impresion listas y puntajes finales
    puts("Lista 1 final\n");
    imprimirSolucion(S1);
    printf("puntaje lista1 final:%d\n", Score1);
    puts("Lista 2 final\n");
    imprimirSolucion(S2);
    printf("puntaje lista2 final:%d\n", Score2);

    borrar(S1);
    borrar(S2);
    borrar(Mejor1);
    borrar(Mejor2);

}
