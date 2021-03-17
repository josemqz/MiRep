#include "stdio.h"
#include "stdlib.h"
#include "fun.h"
#include "linkedList.h"


/*****
*   int fun
******
*   Funcion encargada de entregar la puntuacion de un nodo basado en el tipo del elemento.
*   En el caso de ser entero, depende también de su valor.
******
*   Input:
*       void* node: Puntero a nodo a evaluar
******
*   Retorno:
*       int: Puntaje del nodo
*****/
int fun(void* node){

    int score;

//int
    if (((listNode*)(node))->type == 'i') {
        score = 6 * *(int*)(((listNode*)(node))->data);
    }
//char
    else if (((listNode*)(node))->type == 'c'){
        score = 16;
    }
//bit
    else{
        score = 7;
    }

    return score;
}
