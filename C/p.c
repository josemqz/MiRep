#include <stdio.h>
#include <stdlib.h>
int main(){

    int h = 35;
    int* j;
    j = &h;
    printf("%p\n",j);

    int* y = (int*)malloc(3*sizeof(int));
    y[1] = 10;
    printf("%p\n", y);
    free(y);

    printf("\n");

    float D[2] = {15,200.5};

    float p = D[0];
    printf("%f\n", p);

    float *P = &D[1];
    printf("%f\n",*P);
}
