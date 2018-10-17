#include <stdio.h>
#include <stdlib.h>
#include "Linked.c"

void* cosa(void* x){
    printf("%d\n", (int*) Length(x));
    return x;
}

int main(){
    tLista* L;
    L = BobLink();
    L = cosa(L);
    RalphLink(L);

    void* bla;
    int *x;
    x = (int*)malloc(sizeof(int));
    *x = 5;
    printf("%d\n", *x);

    return 0;
}
