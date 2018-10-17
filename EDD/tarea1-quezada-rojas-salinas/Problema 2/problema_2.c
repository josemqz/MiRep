#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#define maxsize 1000000 //tamanio maximo para un string que contiene una linea de archivo palabras

//struct para archivo palabras
typedef struct{
    int maxPageN;       //cantidad de paginas web que se encuentran por palabras
    int *relatedPgs;    //arreglo que contiene la cantidad de numeros de coincidencias indicada por maxPageN
}words;

//struct para archivo consultas
typedef struct{
    int wordX;  //palabra 1
    int wordY;  //palabra 2
}consulta;


int main() {
//contadores
    int _count = 0,_count2 = 0;
    int i,j,c,w;

    words **word1;
    consulta **ct1;

    FILE *consultas;
    FILE *palabras;
    FILE *salida;

//Apertura de archivos
    consultas = fopen("consultas.dat","r");
    palabras = fopen("palabras.dat","r");
    salida = fopen("salida.dat","w");
//Verficacion de la apertura de archivos
    verify(consultas,(char*)"consultas");
    verify(palabras,(char*)"palabras");
    verify(salida,(char*)"salida");
//Contar cantidad de lineas de ambos archivos
    _count = line_count(palabras, _count);
    _count2 = line_count(consultas, _count2);

//Asignacion de memoria
    word1 = (words**)malloc(_count*sizeof(words*));
    ct1 = (consulta**)malloc(_count2*sizeof(consulta*));

//Posicionarse en el inicio de cada archivo
    fseek(palabras, 0, SEEK_SET);
    fseek(consultas, 0, SEEK_SET);

//Extraccion datos de archivo Consultas
    for (i = 0; i < _count2; i++){
        ct1[i] = (consulta*)malloc(_count2*sizeof(consulta));
        fscanf(consultas, "%d %d", &ct1[i]->wordX, &ct1[i]->wordY);
    }

//Extraccion datos de archivo Palabras
    for(i = 0; i < _count; i++) {
        char sp[]=" ";                //char a utilizar para la separacion
        char linea[maxsize];          //string con tamanio maximo (buffer)
        word1[i] = (words*)malloc(_count*sizeof(words));

        fscanf(palabras,"%d", &word1[i]->maxPageN);
        fgets(linea, maxsize, palabras);
        // Se declara el puntero a utilizar en la funcion strtok
        char *token;
        // A token se le asigna cada valor de la linea separado por un espacio
        token = strtok(linea,sp);
        // Asignacion de memoria del arreglo que contiene las paginas web
        word1[i]->relatedPgs = (int*)malloc(word1[i]->maxPageN*sizeof(int));

        j = 0;
        while(token != NULL) {
            // Coloca cada palabra en un espacio del arreglo
            word1[i]->relatedPgs[j] = atoi(token);
            // Asigna los demas tokens
            token = strtok(NULL,sp);
            j++;
        }
    }

    for (i = 0; i < _count2; i++) {
        findCommon(word1[ct1[i]->wordX]->relatedPgs, word1[ct1[i]->wordX]->maxPageN, word1[ct1[i]->wordY]->relatedPgs, word1[ct1[i]->wordY]->maxPageN, salida);
    }


//liberacion de memoria
    for (w = 0; w < _count; w++) {
        free(word1[w]->relatedPgs);
        free(word1[w]);
    }
    for (c = 0; c < _count2; c++){
        free(ct1[c]);
    }
    free(word1);
    free(ct1);
//cerrar archivos
    fclose(consultas);
    fclose(palabras);
    fclose(salida);

    return 0;
}
