#include <stdio.h>
#include <stdlib.h>
#include "Wa.h"

int main(){

    graphList *G;
    //linkList* Reach;
    int i;
    int N, M, Q;     //N: ciudades / 1 <= N <= 1.000.000 ; M: vuelos / 0 <= M <= 50.000.000
    int O, D, q;

    scanf("%d\n", &N); //ciudades
    scanf("%d\n", &M); //vuelos

    //if (N > 1000000 || N < 0){ puts("men why"); return -1;}   ji
    //if (N > 50000000 || N < 0){ puts("men why"); return -1;}  ji

    G = initGraph(N);

//Insertar nodos en TDA Grafo
    for (i = 0; i < M; i++){
        scanf("%d %d", &O, &D);
        setEdge(G, O, D);
    }


    //PrintGrafo(G);
    //puts("\n");
//Consultas
    scanf("%d\n", &Q);
    for (i = 0; i < Q; i++){
        scanf("%d", &q);

        VisitadontGrafo(G);

        //DFS(G,q);

        Search(G,q);
        printf("\n");

    }
    graphDestroyer(G);

    return 0;
}
