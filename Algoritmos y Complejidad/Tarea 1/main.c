#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include <unistd.h>

// Busqueda Binaria para el numero del nodo dentro del struct
int busquedaNodos(nodo *arrayNodos, int izq, int der, int buscado){
    int med = izq + (der-izq)/2;
    
    if (arrayNodos[med].numero == buscado) return med;
    if (arrayNodos[med].numero > buscado) return busquedaNodos(arrayNodos, izq, med-1, buscado);
    return busquedaNodos(arrayNodos, med+1, der, buscado);
}


int busquedaBinaria(int *array, int izq, int der, int buscado){

    int med = izq + (der-izq)/2;
    
    if (array[med] == buscado)  return med;  //Igual al medio
    if (array[med] > buscado)   return busquedaBinaria(array, izq, med-1, buscado);  //Mayor al medio
    return busquedaBinaria(array, med+1, der, buscado); // Inferior
    
    //NO hay caso en que el elemento no existe.
}

void eliminarConexion(nodo *nodo1, nodo *nodo2){
    int n1 = nodo1->numero, n2 = nodo2->numero, indexN1, indexN2;
    
    printf("%d %d\n", n1, n2);
    
    indexN1 = busquedaBinaria(nodo1->conexiones, 0, nodo1->n_conex-1, n2);
    indexN2 = busquedaBinaria(nodo2->conexiones, 0, nodo2->n_conex-1, n1);

    for (n1 = indexN1; n1 < nodo1->n_conex-1; n1++){
        nodo1->conexiones[n1] = nodo1->conexiones[n1+1];
    }
    for (n2 = indexN2; n2 < nodo2->n_conex-1; n2++){
        nodo2->conexiones[n2] = nodo2->conexiones[n2+1];
    }
    
    nodo1->n_conex-=1;
    nodo2->n_conex-=1;
    
}

// Funcion de comparacion para struct de Nodos, utilizada en Qsort
int cmpfunc(const void *nodo1, const void *nodo2){
    const nodo *n1 = (nodo *)nodo1;
    const nodo *n2 = (nodo*)nodo2;
    
    if (n1->numero < n2->numero)
        return -1;
    else if (n1->numero > n2->numero)
        return +1;
    else
        return 0;
}

void copyArray(int *destino, int *origen, int size2){
    int index;
    for (index = 0; index < size2; index++)
        destino[index] = origen[index];    
}

void eliminarNodo(grafo *Grafo, int index){
    int indexNodo;
    
    free(Grafo->arrayNodos[index].conexiones);
    
    for (indexNodo = index ; indexNodo < Grafo->nNodos-1 ; indexNodo++)
        Grafo->arrayNodos[indexNodo] = Grafo->arrayNodos[indexNodo+1];
       
    Grafo->nNodos -= 1;
}

// Elimina del grafo aquellos nodos que no tienen conexiones.
void analizarGrafo(grafo *Grafo){
    int indexNodo = 0, indexNodo2;// base = 0;

    while (indexNodo < Grafo->nNodos){
        if (Grafo->arrayNodos[indexNodo].n_conex == 1){
            nodo* nodo1 = &Grafo->arrayNodos[indexNodo];
            indexNodo2 = busquedaNodos(Grafo->arrayNodos, 0, Grafo->nNodos, Grafo->arrayNodos[indexNodo].conexiones[0]);
            nodo *nodo2 = &Grafo->arrayNodos[indexNodo2];
            
            eliminarConexion(nodo1, nodo2);
            Grafo->eliminaciones += 1;
            indexNodo = 0;
        }
        else if (Grafo->arrayNodos[indexNodo].n_conex == 0){
            eliminarNodo(Grafo, indexNodo);
            indexNodo = 0;
            //indexNodo++;
        }
        else{
            //base++;
            indexNodo++;
        }
    }
}



// Aplica mergeSort en los arreglos de conexiones de cada nodo, y luego aplica Qsort en la lista de nodos
void sortGrafo(grafo* Grafo){
    int indexNodo = 0;
    
    for (indexNodo = 0; indexNodo < Grafo->nNodos; indexNodo++){
        mergeSort(Grafo->arrayNodos[indexNodo].conexiones, 0, Grafo->arrayNodos[indexNodo].n_conex - 1);
    }
    
    qsort(Grafo->arrayNodos, Grafo->nNodos, sizeof(nodo), cmpfunc);
    // Se tiene el grafo ordenado por numero de nodo, y cada conexion ordenada de menor a mayor

    analizarGrafo(Grafo);
    
}


int main(){
    char dato;
    int indexNodo = 0, indexArray = 1;
    
    FILE* input = stdin;
    
    while ((dato = fgetc(input)) != EOF){
        int limite = (int)dato - 48;
        
        grafo* Grafo = malloc(sizeof(grafo));
        Grafo->arrayNodos = malloc(limite*sizeof(nodo));
        Grafo->nNodos = limite;
        Grafo->eliminaciones = 0;
        
        for (indexNodo = 0 ; indexNodo < limite ; indexNodo++){
            Grafo->arrayNodos[indexNodo].conexiones = malloc(limite*sizeof(int));
            Grafo->arrayNodos[indexNodo].n_conex = 0;
        }
    
        dato = fgetc(input); // Lee el \n despues del numero de nodos en la red.
        indexNodo = 0;
        
        while (indexNodo < limite){
            
            dato = fgetc(input);   // Numero del nodo que se est? leyendo.
            Grafo->arrayNodos[indexNodo].numero = (int)dato-48;
           
            indexArray = 0;
            while (indexArray > -1){
                
                dato = fgetc(input);
                
                if (dato != ' ' && dato != '\n'){
                    Grafo->arrayNodos[indexNodo].conexiones[indexArray] = (int)dato - 48;
                    Grafo->arrayNodos[indexNodo].n_conex++;
                    indexArray++;
                }

                else if (dato == '\n'){
                    indexNodo++;
                    break;
                }
            }    
        }
        
        sortGrafo(Grafo);
        
        if (Grafo->eliminaciones == 0)
            puts("No Existe Corte.");
       
        
        /*
        for (indexNodo = 0 ; indexNodo < Grafo->nNodos ; indexNodo++){
            int x = 0;
            printf("%d ", Grafo->arrayNodos[indexNodo].numero);
            for (x = 0 ; x < Grafo->arrayNodos[indexNodo].n_conex ; x++){
                printf("%d ", Grafo->arrayNodos[indexNodo].conexiones[x]);
            }
            puts("\n");
        }
        */
        
        for (indexNodo = 0 ; indexNodo < Grafo->nNodos ; indexNodo++){
            free(Grafo->arrayNodos[indexNodo].conexiones);
        }
        free(Grafo->arrayNodos);
        free(Grafo);
        puts("\n");
    } 
    return 0;
}