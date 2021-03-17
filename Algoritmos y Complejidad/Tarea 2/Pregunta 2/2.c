#include <stdio.h>
#include <stdlib.h>


int pseudobinaria(int* Arr, int n, int valor){
    int izq = 0;
    int der = n - 1;
    int mid;
    while (izq < der){
        mid = (izq + der)/2;
        if (Arr[mid] < valor) izq = mid + 1;
        else der = mid - 1;
    }
    if (izq == der){
        if(Arr[izq] > valor) return Arr[izq - 1];
        else return Arr[izq];
    }
    return -1;
}


int main(int argc, char const *argv[]) {

    FILE* fp = fopen(argv[1],"r");
    int N, Q, v, P;

    while (!feof(fp)){

        fscanf(fp, "%d\n", &N);

        //arreglo con parentesis que representan el arbol
        char* arbol = (char*) malloc (sizeof(char) * (2*N + 1));     //2n
        fscanf(fp, "%s\n", arbol);

        //valores de cada nodo
        int* valores = (int*) malloc (sizeof(int) * N);       //n
        int i;
        for(i = 0; i < N; i++) {
            fscanf(fp, "%d ", &valores[i]);
        }

        //nivel en que se encuentra cada nodo
        int* niveles = (int*) malloc (sizeof(int) * N);
        int nivel = 0;
        int arb_index;
        i = 0;
        for(arb_index = 0; arb_index < 2*N; arb_index++){

            if(arbol[arb_index] == '('){
                niveles[i] = nivel;
                nivel++;
                i++;
            }
            else if(arbol[arb_index] == ')'){
                nivel--;
            }
        }


        fscanf(fp, "%d\n", &Q);

        int j = 0;
        while (j < Q){                                      //Q veces

            fscanf(fp, "%d %d\n", &v, &P);

            int k;
            int resultado = valores[v];
            int actual = niveles[v]; //nivel del nodo v
            int flag = 0;

            for (k = v - 1; niveles[k] > 1; k--){
                //se encuentra a un ancestro
                if (niveles[k] < actual){

                    actual = niveles[k];

                    if(valores[k] > P){
                        resultado = valores[k];
                    }
                    else{
                        flag = 1;
                        break; //ya se tiene el resultado
                    }

                }
            }

            //nivel 1 de arbol
            if (flag != 1 && niveles[k] == 1){

                actual = 1;

                if(valores[k] > P){
                    if(valores[0] > P){
                        resultado = valores[0];
                    }
                    else resultado = valores[k];
                }
            }


/*
    Se debe contar con un archivo de texto que contenga los datos especificados en la pauta
    Escribir por consola "gcc 2.c -Wall -o d && ./d <archivo de texto>"

*/

            printf("Resultado: %d\n", resultado);

            j++;
        }

        puts("");

        free(arbol);
        free(valores);
        free(niveles);

    }

    fclose(fp);
    return 0;
}
