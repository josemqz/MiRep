#include <stdio.h>
#include <stdlib.h>

int F(int x){
    while(x < 100){
        x--;
        x = F(x);
    }
}

int main(){
    int a;
    char b[20];

    scanf("%d", &a);
    scanf("%s", b);

    printf("%d\n", a);
    printf("%s\n", b);
    return 0;
}
