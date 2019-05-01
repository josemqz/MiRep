#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define maxsize 1000000 //tamaño maximo para un string que contiene una linea de archivo palabras

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
int verify (FILE *a, char *b){
    if( a == NULL){
        printf("Archivo %s no pudo abrirse.\n", b);
        exit(1);
    }
    return 0;
}

/*****
*   int cmpfunc
******
*   Compara dos variables y retorna su valor de verdad.
******
*   Input:
*       const void * a : constante de un cierto tipo a comparar
*       const void * b : constante de un cierto tipo a comparar
*        ......
******
*   Returns:
*       int, 0 o 1, dependiendo de si es verdadera o no la comparación.
*****/
//funcion de comparacion para findCommon
int cmpfunc(const void * a, const void * b){
    return(*(int*)a > *(int*)b);
}


/*****
*   int findCommon
******
*   Funcion que toma dos arreglos y su tamaño y copia la interseccion en un nuevo archivo.
*   Primero ordena los arreglos en orden ascendente para luego iterar sobrre ellos.
******
*   Input:
*       int *arr1   :   arreglo de enteros
*       int len1    :   entero, tamaño del arreglo 1
*       int *arr2   :   arreglo de enteros
*       int len2    :   entero, tamaño del arreglo 2
*       FILE *file1 :   puntero a archivo
*        ......
******
*   Returns:
*       int, retorna 0 al concluir la funcion.
*****/
//
int findCommon(int *arr1, int len1, int *arr2, int len2, FILE* file1) {

    qsort(arr1,len1,sizeof(int),cmpfunc);
    qsort(arr2, len2, sizeof(int), cmpfunc);

    int *arr3;
    int i = 0;
    int j = 0;
    int k = 0;
    char s[maxsize];
    arr3 = (int*)malloc(sizeof(int));
    while(len1 > i && len2 > j){
        if (arr1[i] < arr2[j]) {
           i++;
        }
        else if(arr2[j] < arr1[i]){
            j++;
        }
        else {
            k++;
            arr3 = (int*)realloc(arr3,k*sizeof(int));
            arr3[k-1] = arr1[i];
            i++, j++;
        }
    }

    sprintf(s,"%d",arr3[0]);
    for (i = 1; i < k; i++) {
        sprintf(s,"%s %d",s, arr3[i]);
    }

    if (k != 0){
        fprintf(file1, "%d %s\n",k,s);
        free(arr3);
        return 0;
    }
    else{
        fprintf(file1, "%d\n", 0);
        free(arr3);
        return 0;
    }
    free(arr3);
}

/*****
*   int line_count
******
*   Funcion cuyo objetivo es contar la cantidad de lineas de un archivo.
******
*   Input:
*       FILE *arch : variable que apunta a archivos.
*       int count : variable funciona como contador, el que aumenta cuando se completa una linea.
*        ......
******
*   Returns:
*       int, numero de lineas de un archivo
*****/
int line_count(FILE *arch, int count){
    while(!feof(arch)){
        char a = fgetc(arch);
        if(a == '\n'){
            count++;
        }
    }
    return count;
}
