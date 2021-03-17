#include <stdio.h>
#include <stdlib.h>

int main(){
  int neo[20][20];
  int i,j;

  FILE *test = fopen("test.txt","r");
  int c = (int)fgetc(test) - 48;
  int a,b;

  for (i = 0; i < 20; i++){
    for (j = 0; j < 20; j++){
      neo[i][j] = 0;
    }
  }

  for (i = 0; i < c; i++)
  {
      fscanf(test,"%d %d",&a,&b);
      neo[a][b] = 1;
  }

  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 20; j++)
    {
      printf("%d ", neo[i][j]);
    }
    printf("\n");
  }
  /*
  for(i = 0; i < 40; i++)
  {
  }*/
  return 0;
}
