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
    in = fopen("in.txt","r");
    out = fopen("out.txt","w");

//Verificacion archivo in
    verify(in,"in.txt");

//Lectura de cantidad de polinomios
    int M;
    fscanf(in,"%d", &M);

//Arreglo de listas enlazadas
    tPoli** PAUL = (tPoli**)malloc(M*sizeof(tPoli*));

//Lectura archivo in
    for (i = 0; i < M; i++){
    //Lectura de cantidad de monomios
        int N;
        fscanf(in,"%d", &N);
    //Inicializacion de polinomio i
        PAUL[i] = BobLink();
        for (j = 0; j < N; j++){
            int e, c;   //expo y coef
            fscanf(in,"%d %d", &e, &c);
            Insert(PAUL[i], c, e);
        }
    }

//printf("%d\n", PAUL[2]->tail->coef);

//Lectura de funciones
char A[20];
int p,q;
while(fscanf(in,"%s %d %d",A,&p,&q) > 0){

    if (strcmp(A,"EVALUAR") == 0){
        puts("d");
        Evaluar(PAUL, M, p, q, in, out);
    }
    else if (strcmp(A,"COEFICIENTE") == 0){
        fprintf(out, "%d\n", Coeficiente(PAUL, M, p, q));
    }
    else{
        puts("Error: arreglo de caracteres incorrecto\n"); //ji
    }
}

//Liberacion de memoria
    for (i = 0; i < M; i++){
        Clear(PAUL[i]);
        RalphLink(PAUL[i]);
    }
    free(PAUL);

//Cierre de archivos
    fclose(in);
    fclose(out);

    return 0;
}
