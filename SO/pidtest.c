#include <stdio.h>
#include <unistd.h>

void main(){
	
	int cpid = fork();
	if (cpid == 0){
		printf("pid proceso hijo: %d\n", getpid());
	}
	else{
		printf("pid actual: %d\n", cpid);
	}
	printf("algun pid: %d\n", getpid());

	int i,j;
	for (i=0; i<3; i++){
		//pid = getpid();
		printf("i: %d\n", i);
		for (j=0; j<3 ; j++){
			//nuevo = fork();/* 1 */
			//puts("ble1");
			printf("j: %d\n", j);
			if (i == 1){
				//nuevo = fork();/* 2 */
				break;
			}
		}
	}
}
