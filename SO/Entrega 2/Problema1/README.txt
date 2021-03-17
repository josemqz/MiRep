Para ejecutar el programa se debe utilizar el comando "make", y luego "java Problema1", manteniendo el
archivo de funciones.txt en la misma carpeta que el programa.

Preferentemente, se deberian tener las funciones juntas dentro del txt. Es decir, si se indica que hay 3
lineas con funciones, estas deberian estar en las 3 lineas siguientes.

(No es seguro que vaya a funcionar teniendo espacios entre lineas).
Tambien, el programa se hizo pensando en que no existen espacios dentro de una funcion
es decir, las funciones se encuentran en el tipo "x+1" en vez de "x + 1"

El programa tambien pide operaciones indefinidamente, hasta que se corte con Ctrl-C

En cuanto al uso de threads, se utiliza un thread para cada llamada a función, pero estas no son pre-calculadas,
ya que no se asume su contenido, ya que, si bien, si f(x) llama a g(x) y h(x), podrían precalcularse ambas, para que
estén listas cuando sean llamadas por f(x), pero el programa espera a que sea su turno de evaluarse, ya que se
permite que se evaluen con funciones dentro del parametro, tipo f(x)=g(x+1)*h(2*x-1), por lo que no se
asume que su contenido siempre será unicamente X.

Por otro lado, x siempre será el valor de la incognita, ya que el programa directamente reemplaza x por su valor,
por lo que además se recomienda no tener funciones llamadas x(...)=..., ya que puede no dar el resultado
correcto según como estén anidadas. (No es un error como tal, si no que está hecho para que x solo sea una variable)

Por ultimo, solo se trabaja con numeros enteros, por lo que dividir de forma inexacta perderá el resto.
