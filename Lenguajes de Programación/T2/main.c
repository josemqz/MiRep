#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "genetico.h"
#include "fun.h"


int main(){

	time_t t;

	int f = 0;
	if (f == 0){
		srand((unsigned) time(&t));
		f = 1;

	}

	genetico(mutacionTipo, cruceMedio, 10, 100);

    return 0;

}
