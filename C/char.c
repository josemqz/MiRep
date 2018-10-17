#include <stdio.h>
#include <string.h>

void main(){
    char j[5] =  {'h','o','l','a','\0'};
    char* p = &j[1];
    printf("%c\n",*p);

    char P = j[3];
    printf("%c\n",P);

    char A[5] = {'h','o','k','b','\0'};
    printf("%d\n", strcmp("hola",A));
}
//a[i] == *(a + i)
