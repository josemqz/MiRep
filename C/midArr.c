#include <stdio.h>

int main(){
    int d;
    scanf("%d", &d);

    int A[d];
    int i, a;
    for(i = 0; i < d; i++){
        A[i] = i;
    }
    a = A[(d-1)/2];
    printf("%d\n", a);
    return 0;
}
