
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

//Estructura de nodo
typedef struct node{
    void* data;
    char type; // "i","c","b"
    struct node* next;
}listNode;

//Estructura de lista enlazada
typedef struct {
    listNode* head;
    listNode* tail;
    listNode* curr;
    int listSize;
    int pos;
}linkList;


/*****
*   void* getRand
******
*   Establece los elementos de un nodo de manera aleatoria
******
*   Input:
*       listNode*: Nodo sin información
******
*   Retorno:
*       void*: Nodo compuesto por información aleatoria
*****/
void* getRand(listNode* node){

    char* a[] = {"i","c","b"};                          //arreglo con tipos de datos
    char* b[] = {"A","B","C","D","E","F"};              //arreglo con distintos caracteres

    char i = *a[rand() % 3];                            //eleccion al azar de tipo a partir del arreglo "a"
    ((listNode *)node)->type = i;                       //asignacion de tipo de dato del nodo

//int
    if (i == 'i') {

    	int* data2 = (int*)malloc(sizeof(int));         //asignacion de memoria a puntero a elemento de tipo entero
    	*data2 = rand() % 10;                           //elección al azar de elemento de tipo entero entre 0 y 9
    	((listNode*)node)->data = data2;                //asignacion al dato del nodo
    }

//char
    else if (i == 'c') {

    	char* data2 = (char*)malloc(sizeof(char));      //asignacion de memoria a puntero a elemento de tipo char
    	*data2 = *b[rand() % 6];                        //elección al azar de elemento de tipo entero a partir de arreglo "b"
    	((listNode*)node)->data = data2;                //asignacion al dato del nodo
    }

//bit
    else{

    	int* data2 = (int*)malloc(sizeof(int));         //asignacion de memoria a puntero a elemento de tipo entero
    	*data2 = rand() % 2;                            //elección al azar de elemento de tipo entero entre 0 y 2
        ((listNode*)node)->data = data2;                //asignacion al dato del nodo
    }

//nodo con elemento al azar
    return node;
}


/*****
*   void* generateNode
******
*   Inicializa un nodo y ocupa función para introducir la información de él
******
*   Input:
*       Nada
******
*   Retorno:
*       void*: Nodo inicializado y compuesto por información aleatoria
*****/
void* generateNode(){
    listNode* node = (listNode*)malloc(sizeof(listNode));   //asignación de memoria a puntero a nodo de tipo listNode*
    node = (listNode*)getRand(node);                        //funcion que incorpora un elemento aleatorio al nodo

//nodo inicializado
    return node;
}


/*****
*   void Next
******
*   Mueve el puntero a la posicion actual de la lista al siguiente elemento
******
*   Input:
*       tPoli* P: Puntero a lista enlazada P
******
*   Retorno:
*       Nada
*****/
void next(void* List) {

    if (((linkList*)(List))->curr != ((linkList*)(List))->tail) {

        ((linkList*)(List))->curr = ((linkList*)(List))->curr->next;
        ((linkList*)(List))->pos++;
    }
}


/*****
*   int getSize
******
*   Retorna el largo de una lista enlazada
******
*   Input:
*       void* List: Lista enlazada de cualquier tipo
******
*   Retorno:
*       ((linkList*)(List))->listSize: Largo de lista enlazada
*****/
int getSize(void* List){
    return ((linkList*)(List))->listSize;
}


/*****
*   void MoveToStart
******
*   Mueve el puntero con la posicion actual de la lista al inicio de esta
******
*   Input:
*       void* P: lista de monomios en la cual se quiere mover la posicion
******
*   Retorno:
*       Nada
*****/
void moveToStart(void* List){

    ((linkList*)(List))->curr = ((linkList*)(List))->head;
    ((linkList*)(List))->pos = 0;
}


/*****
*   void MoveToPos
******
*   Mueve el puntero de la posicion actual a la deseada
******
*   Input:
*       int pos: Posición deseada
*       linkList*: Lista enlazada
******
*   Retorno:
*       Nada
*****/
void moveToPos(int pos, linkList* List) {

    moveToStart(List);

    while(List->pos != pos){
        next(List);
    }
}


/*****
*   void/ generarSolucion
******
*   Inicializa una lista enlazada y agrega elementos aleatorios de tipo entero, caracter o bit, elegidos al azar
******
*   Input:
*       int largo: largo de lista
******
*   Retorno:
*       void* L: Lista enlazada de largo "largo"
*****/
void* generarSolucion(int largo){

    linkList* L = (linkList*)malloc(largo*sizeof(linkList));
    int i;
    L->curr = L->head = L->tail = (listNode*)generateNode();
    L->curr->next = NULL;
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
*       void* Lista: Lista enlazada a copiar
******
*   Retorno:
*       void* L: Lista enlazada, copia de "Lista"
*****/
void* copiar(void* Lista){
    int size = ((linkList*)Lista)->listSize;
    linkList *L = (linkList*)malloc(size*sizeof(linkList));
    int i;
    L->curr = L->head = L->tail = (listNode*)generateNode();
    L->curr->next = NULL;
    for (i = 1; i < size; i++) {
        L->tail->next = (listNode*)generateNode();
        L->tail = L->tail->next;
    }
    L->listSize = size;
    return L;
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
    listNode* node = ((linkList*)Lista)->head;
    listNode* nxt;
    while (node != NULL) {
        nxt = node->next;
        free(node->data);
        free(node);
        node = nxt;
    }
    ((linkList*)Lista)->head = NULL;
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
    for (i = 0; i<((linkList*)(Lista))->listSize; i++) {

         if (((linkList*)(Lista))->curr->type == 'c') {
            printf("data:%c\ttype:%c\n",  *((char*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }
        else{
            printf("data:%d\ttype:%c\n", *((int*)((linkList*)(Lista))->curr->data), ((linkList*)(Lista))->curr->type);
        }
        next((linkList*) Lista);
    }
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

    int a = (((linkList*)(Lista1))->listSize)/2-1; //elemento posterior a mitad
    int b = (((linkList*)(Lista2))->listSize)/2-1;

    moveToPos(a,((linkList*)(Lista1)));
    moveToPos(b,((linkList*)(Lista2)));

    listNode* P1 = ((linkList*)Lista1)->curr->next;

    ((linkList*)Lista1)->curr->next = ((linkList*)Lista2)->curr->next;
    ((linkList*)Lista2)->curr->next = P1;

    listNode* H1 = ((linkList*)(Lista1))->head;
    listNode* H2 = ((linkList*)(Lista2))->head;

    ((linkList*)Lista1)->head = H2;
    ((linkList*)Lista2)->head = H1;

    int nSize = (((linkList*)Lista1)->listSize + ((linkList*)Lista2)->listSize)/2;

    ((linkList*)Lista1)->listSize = nSize;
    ((linkList*)Lista2)->listSize = nSize;

    imprimirSolucion(Lista1);
    printf("diferenciar las dos\n");
    imprimirSolucion(Lista2);
};


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

    int domo = rand() % ((linkList*)Lista)->listSize;
    moveToPos(domo,((linkList*)Lista));

    ((linkList*)Lista)->curr->type = *a[rand()%3];

    int flag = 1;

    if (((linkList*)Lista)->curr->type == 'i'){
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%10;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (int*)malloc(sizeof(int));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else if (((linkList*)Lista)->curr->type == 'c') {
     	char* data2 = (char*)malloc(sizeof(char));
        while(flag != 0){
            *data2 = *b[rand()%6];
            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (char*)malloc(sizeof(char));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else{
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%2;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                free(((linkList*)Lista)->curr->data);
                ((linkList*)Lista)->curr->data = (int*)malloc(sizeof(int));
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }
}


/*****
*   void mutacionRand
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

    if (((linkList*)Lista)->curr->type == 'i'){
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%10;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else if (((linkList*)Lista)->curr->type == 'c') {
     	char* data2 = (char*)malloc(sizeof(char));
        while(flag != 0){
            *data2 = *b[rand()%6];
            if (*data2 != *((char*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }

    else{
        int* data2 = (int*)malloc(sizeof(int));
        while(flag != 0){
            *data2 = rand()%2;
            if (*data2 != *((int*)((linkList*)Lista)->curr->data)) {
                ((linkList*)Lista)->curr->data = data2;
                flag = 0;
            }
        }
    }
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










}


/*****
*   void evaluacionLista
******
*   Aplica una funcion que evalua cada nodo, y retorna la sumatoria de las evaluaciones
******
*   Input:
*       int (*fun)(void*): Funcion de evaluacion
*       void* Lista: Lista enlazada a evaluar
******
*   Retorno:
*       int: Evaluacion total de la lista enlazada
*****/
int evaluacionLista(int (*fun)(void*), void* Lista);


/*****
*   void genetico
******
*   Se crean dos listas enlazadas de elementos aleatorios, las que son evaluadas.
*   Luego, se aplica un cruce entre ellas, generando dos listas nuevas, las que
*   reemplazarán a las originales en caso de ambas tener una mayor mayor puntuación.
*   Después de esto, se aplica una mutación a las nuevas listas y se evalúan.
*   Si una de ellas supera a su homóloga original, reemplaza a esta.
*   Todo esto se repite una cantidad "iteraciones" de veces.                            LOL
******
*   Input:
*       void (*muta)(void*): Función de mutación de listas enlazadas
*       void (*cruce)(void*): Función de cruce entre listas enlazadas
*       int n: Largo de listas
*       int iteraciones: Cantidad de veces a repetir las operaciones
******
*   Retorno:
*       Nada
*****/
void genetico(void (*muta)(void*), void (*cruce)(void*), int n, int iteraciones);
