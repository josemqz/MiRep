#include <unistd.h>
#include <stdio.h>

void main(){
    int f = fork();

    if (f == 0){
        printf("%d\n", getpid());
        puts("hey");

        f = fork();
        if (f == 0){
            printf("%d\n", getpid());
            puts("dis is gs");
        }
        else{
            printf("%d\n", getpid());
            puts("este deberia ser el mismo pid que salio unas lineas antes ji");
        }
    }
    else{
        printf("%d\n", getpid());
        puts("ho");
    }
    printf("%d\n", getpid());
    puts("let's go");
}
