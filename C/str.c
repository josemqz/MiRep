#include <stdio.h>
#include <stdlib.h>

int main(){
    //THIS BAD
/*
    char* p = (char*)malloc(4*sizeof(char));
    p = "bla";
    printf("%s\n", p);
    free((p);
*/
    //----------------------------------------
    //THIS GOOD
    char x[] = "bla";
    printf("%s\n", x);
    //BECAUSE YES
    return 0;
}
