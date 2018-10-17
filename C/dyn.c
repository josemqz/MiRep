#include <stdio.h>
#include <stdlib.h>
/*Memoria dinamica
Malloc -> asignar memoria, free ->liberar
*/

int main(){

int* p;
p = (int*)malloc(sizeof(int)); //(int*) no necesario, ji.
p = 5;
printf("%p\n",p);
free(p);

return 0;
}

//gdb (debugger)
//valgrind (mem-check)
