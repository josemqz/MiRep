#include <stdio.h>
#include <stdlib.h>


void merge(int conexiones[], int izq, int med, int der){ 
    
    int indexIzq, indexDer; 
    int sizeIzq = med - izq + 1, sizeDer =  der - med;
    int arrIzq[sizeIzq], arrDer[sizeDer]; 
  
    for (indexIzq = 0; indexIzq < sizeIzq; indexIzq++)  arrIzq[indexIzq] = conexiones[izq + indexIzq]; 
    for (indexDer = 0; indexDer < sizeDer; indexDer++)  arrDer[indexDer] = conexiones[med + 1+ indexDer]; 
  
    indexIzq = 0, indexDer = 0;  
    int i = izq; 
    
    while (indexIzq < sizeIzq && indexDer < sizeDer){ 
        if (arrIzq[indexIzq] <= arrDer[indexDer]){ 
            conexiones[i] = arrIzq[indexIzq]; 
            indexIzq++; 
        } 
        
        else{ 
            conexiones[i] = arrDer[indexDer]; 
            indexDer++; 
        }
        i++; 
    } 
  
    while (indexIzq < sizeIzq){ 
        conexiones[i] = arrIzq[indexIzq]; 
        indexIzq++; 
        i++; 
    } 
  
    while (indexDer < sizeDer){ 
        conexiones[i] = arrDer[indexDer]; 
        indexDer++; 
        i++; 
    } 
} 
  
void mergeSort(int conexiones[], int izq, int der){ 
    if (izq < der){ 
        int med = izq + (der-izq)/2; //Calculo de la mitad
        mergeSort(conexiones, izq, med); 
        mergeSort(conexiones, med+1, der);
        merge(conexiones, izq, med, der); 
    } 
}