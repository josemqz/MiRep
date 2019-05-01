#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones.h"

int main(){
//Asignacion variables
    int i,j;
    FILE* in;
    FILE* out;

//Apertura archivos
    in = fopen("entradaPolinomio.txt","r");
    out = fopen("salidaPolinomio.txt","w");

//Verificacion archivo in
    verify(in,"in.txt");

//Lectura de cantidad de polinomios
    int M;
    fscanf(in,"%d", &M);

//Arreglo de listas enlazadas
    tPoli** POLI = (tPoli**)malloc(M*sizeof(tPoli*));

//Lectura archivo in
    for (i = 0; i < M; i++){
    //Lectura de cantidad de monomios
        int N;
        fscanf(in,"%d", &N);
    //Inicializacion de polinomio i
        POLI[i] = constLista();
        for (j = 0; j < N; j++){
            int e, c;   //expo y coef
            fscanf(in,"%d %d", &e, &c);
            Insert(POLI[i], c, e);
        }
    }


//Lectura de funciones
char A[20];
int p,q;
float x;
while(fscanf(in,"%s",A) > 0){

    if (strcmp(A,"EVALUAR") == 0){
        fscanf(in, "%d %f", &p, &x);
        Evaluar(POLI, M, p, x, out);
    }
    else if (strcmp(A,"COEFICIENTE") == 0){
        fscanf(in, "%d %d", &p, &q);
        fprintf(out, "%d\n", Coeficiente(POLI, M, p, q));
    }
    else{
        puts("Error: arreglo de caracteres incorrecto\n"); //ji
        //printf("%d\n", p);
    }
    printf("%s\n", A);
}

//Liberacion de memoria
    for (i = 0; i < M; i++){
        Clear(POLI[i]);
        destructorLista(POLI[i]);
    }
    free(POLI);

//Cierre de archivos
    fclose(in);
    fclose(out);

    return 0;
}
