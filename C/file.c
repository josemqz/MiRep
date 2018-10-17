#include <stdio.h>

int main(){
  FILE *fp; //puntero tipo FILE
  fp = fopen("hey.txt","w");
  //x = fread( * * )
  //fscanf()
  fprintf(fp, "%s\n","bla.");
  /*if (fp == NULL){
    perror("Vacio");
    exit(EXIT_FAILURE);}*/
  while (!feof(fp)){
    //(...)
  }
  fclose(fp);

//Binario

  FILE *f = fopen("algo.dat","wb");
  char A[5] = "hola";
  fwrite(A, sizeof(A),1,f);
  fclose(f);

  FILE *F = fopen("algo.dat","r");
  if(F == NULL) return -1;
  char mander[10];
  fread(mander, sizeof(mander),1,F);
  printf("%s\n", mander);
  fclose(F);
  return 1;
//x = fread(&i, sizeof(int),1,fp) EJEMPLO
}
