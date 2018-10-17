#include <stdio.h>
#include <stdlib.h>

int range(int* p, int n){
  for (int i = 0; i < n; i++){
    p[i] = i;
  }
  return 0;
}

int main(){
  int t, u;
  printf("%s\n", "rango:");
  scanf("%i", &t);
  int* R = (int*)malloc(t*sizeof(int));
  range(R,t);
  for (u = 0; u < t; u++){
    printf("%d\n",R[u]);
  }
free (R);
return 0;
}
