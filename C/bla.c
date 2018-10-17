#include <stdio.h>
#include <string.h>

struct dedatos{
  int egral[10];
  double kill;
};

int main(){
  int pikachu = 3;
  int ha = 2;
  int T[14];


  T[10] = pikachu;
  printf("%d\n", T[10]);

  printf ("%s\n","bla");

  int* framundo;
  framundo = &ha;
  int f = ha;

  printf("var: %d, ubicacion: %p, wea:%d\n",ha, framundo, f);

  struct dedatos dd;
  dd.kill = 2.546;
  printf("%f\n", dd.kill);

for(int i = 0; i <= 8; i += 2){
    printf("hay %d pikachus\n",i);
}
return 0;
}
//%lu -> size
