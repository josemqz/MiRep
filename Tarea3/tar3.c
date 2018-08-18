#include <stdio.h>
#include <stdlib.h>
#include "Wa.h"

int main(){

    graphList *G;
    int i, N, M, Q;     //N: ciudades / 1 <= N <= 1.000.000 ; M: vuelos / 0 <= M <= 50.000.000
    int O, D, q;

    scanf("%d\n", &N);
    scanf("%d\n", &M);

    G = initGraph(N);

    for (i = 0; i < M; i++){
        scanf("%d %d", &O, &D);
        setEdge(G, O, D);   //Insertar en TDA
        printf("%d %d\n", O, D);
    }

    printf("curr :%d\n", G->array[0]->curr->numbr);

    scanf("%d\n", &Q);
    for (i = 0; i < Q; i++){
        scanf("%d", &q);
    //Buscar nodos no conectados a q
        //DFS(G,q);
    }


/*/TEST
    listInsert(G->array[1],5);
    listInsert(G->array[1],4443);
    listInsert(G->array[1],5);

    listInsert(G->array[6],0);
    listInsert(G->array[6],0);
    listInsert(G->array[6],3456789);

    moveToStart(G->array[6]);
    moveToStart(G->array[1]);
    while (G->array[1]->curr != G->array[1]->tail){
        printf("%d\n", G->array[1]->curr->numbr);
        printf("p: %d\n", G->array[1]->pos);
        next(G->array[1]);
    }
        printf("%d\n", G->array[1]->curr->numbr);

    while (G->array[6]->curr != G->array[6]->tail){
        printf("%d\n", G->array[6]->curr->numbr);
        printf("p: %d\n", G->array[6]->pos);
        next(G->array[6]);
    }
    printf("%d\n", G->array[6]->curr->numbr);
//END TEST*/

    graphDestroyer(G);
    return 0;
}
