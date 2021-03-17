#ifndef SORTING_H
#define SORTING_H


typedef struct nodo{
    int numero;
    int* conexiones;
    int n_conex;
}nodo;

typedef struct grafo{
    nodo *arrayNodos;
    int nNodos;
    int eliminaciones;
}grafo;


void merge(int conexiones[], int izq, int med, int der);
void mergeSort(int conexiones[], int izq, int der); 


#endif	// SORTING_H

