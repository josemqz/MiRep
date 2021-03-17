README PROBLEMA 2:

Para compilar el programa solo es necesario utilizar el comando "make" desde la terminal, teniendo los archivos.

Se incluye:

	Problema2.java
	Readme.txt
	Makefile
	input.txt (Es un ejemplo mio).


Para ejecutar el programa se debe tener un archivo llamado "input.txt" como el incluido.
Debe contener numeros separados por espacio.

El programa mostrará por pantalla los numeros que se ingresaron, en el orden ingresado, y luego se mostrará
el resultado ordenado de mayor a menor.


En cuanto al uso de Threads:

El programa implementa el algoritmo Mergesort, donde cada iteración de esta función utiliza un nuevo Thread.
Esto quiere decir que, al aplicar la metodología de "Dividir y Conquistar", cada División utiliza un nuevo thread.

Por lo tanto se tiene el Thread Principal, y luego se crean 2 threads nuevos para mergeSort(MitadIzquierda) y 
mergeSort(MitadDerecha), y el programa continua dividiendo y creando Threads hasta llegar a listas de tamaño 1.

Como la parte "merge" tambien es parte de la función MergeSort, esto implica que tanto las divisiones como los merge
se realizan en Threads por separado.

Entonces, un Thread es creado por una invocación de MergeSort. Luego, este Thread crea 2 Threads nuevos para las
distintas mitades, las cuales hacen lo mismo, y, finalmente, el mismo Thread aplica "merge" de los resultados
de las 2 Threads que creó.


Fin. :^)
