#include <stdio.h>
#include <stdlib.h>

void Leer(int* p){
  for (int i = 0; i < 10; i++){
    printf("%s\n", "Número:");
    scanf("%d",&p[i]);  //&(p[i])
    printf("%d\n", p[i]);
  }
}

int main(){
  int Ar[10];
  int *p;
  //p = (int *)malloc(10*sizeof(int *));
  p = Ar;
  Leer(p);
  long suma = 0;
  for (int y = 0; y < 10; y++){
    suma += (long)Ar[y];
  }
  printf("suma: %li\n", suma);
  //free(p);
  return 0;
}
