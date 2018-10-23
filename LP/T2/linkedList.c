#include "time.h"
#include "linkedList.h"


/*****
*   void next
******
*   Mueve el puntero a la posicion actual de la lista al siguiente elemento
******
*   Input:
*       void* List: Puntero a lista enlazada de cualquier tipo
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
*       void* List: Puntero a lista enlazada de cualquier tipo

******
*   Retorno:
*       int: Largo de lista enlazada
*****/
int getSize(void* List){
    return ((linkList*)(List))->listSize;
}

/*****
*   void MoveToStart
******
*   Mueve el puntero de la posicion actual de la lista al inicio de esta
******
*   Input:
*       void* List: Puntero a lista enlazada de cualquier tipo
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
*       linkList* List: Lista enlazada
******
*   Retorno:
*       Nada
*****/
void moveToPos(int pos, linkList* List) {
    moveToStart(List);
    while( List->pos !=pos ){
        next(List);
    }
}


/*****
*   void* getRand
******
*   Establece los elementos de un nodo de manera aleatoria
******
*   Input:
*       listNode* node: Nodo con elemento sin valor
******
*   Retorno:
*       void*: Nodo compuesto por información aleatoria
*****/
void* getRand(listNode* node){

    char* a[] = {"i","c","b"};                        //arreglo con tipos de datos
    char* b[] = {"A","B","C","D","E","F"};            //arreglo con distintos caracteres

    char i = *a[rand() % 3];                          //eleccion al azar de tipo a partir del arreglo "a"
    ((listNode *)node)->type = i;                     //asignacion de tipo de dato del nodo

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
    	*data2 = rand() % 2;                            //elección al azar de elemento de tipo entero entre 0 y 1
        ((listNode*)node)->data = data2;              //asignacion al dato del nodo
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
    return node;
}
