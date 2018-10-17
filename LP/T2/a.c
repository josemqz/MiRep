#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "genetico.h"


int main(){

	time_t t;

	int f = 0;
	if (f==0){
		srand((unsigned) time(&t));
		f = 1;

	}
	linkList* Li;
	Li = (linkList*) generarSolucion(15);

	imprimirSolucion(Li);

	borrar(Li);


    return 0;

}
