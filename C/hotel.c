#include <stdio.h>
#include <string.h>

struct Hotel{
  char Nombre[20];
  char Pais[20];
  char Ciudad[20];
  int  Costo;
}H1;

void main(){

struct Hotel H1;
char n[20];
char p[20];
char cit[20];
int cost;

scanf("Nombre: %s",n);
scanf("Pais: %s",p);
scanf("Ciudad: %s", cit);
scanf("Costo por noche:%d", cost);

strcpy(H1.Nombre,n);
strcpy(H1.Pais,p);
strcpy(H1.Ciudad,cit);
H1.Costo = cost;

printf("%s\n", H1.Nombre); //wtf slklsdkfj
}
