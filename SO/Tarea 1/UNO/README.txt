
Ian Perez     201773549-K
José Quezada  201773528-7


Para ejecutar el programa basta con tener instalado gcc y utilizar un terminal en Linux.
Instrucciones de ejecución:
    Abrir terminal en la carpeta del programa
    > make
    > make run


Una vez que el juego inicie, creará una carpeta llamada "Juego" donde se contendrán todos los archivos.

"Jugadores" contiene la mano de cada jugador
"Mazo" todas las cartas que siguen en el mazo
"Last" la ultima carta jugada


Se asume que al sacar una carta, si se puede jugar, se hace sin que el jugador decida,
pasando el turno en caso contrario.

Si la primera carta en juego es negra, el primer jugador que corresponda puede elegir
la carta que desee, así implícitamente eligiendo el color.


IMPORTANTE NOTAR: Cuando se da la opción de elegir que carta jugar, solo se pueden ingresar valores enteros.
		En caso de colocar chars o strings el programa puede causar problemas no deseados.

		you have been warned e_e  pls don't srsly

  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
Isnformación de carta obtenida en analizarCarta()
  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
En el programa se utiliza una notación (infoCarta) compuesta por dígitos y caracteres
que facilita el análisis de los distintos casos determinados por la última jugada y la actual.

//infoCarta : color + tipo carta + numero o caracter de tipo + orientacion
//tipo carta : 0 = numero, 1 = reversa, 2 = comodin, 3 = bloqueo, 4 = +2, 5 = +4
//color : 0 = negro, 1 = rojo, 2 = azul, 3 = verde, 4 = amarillo

(al final nos dimos cuenta de la redundancia que surge entre el dígito de tipo carta
y el caracter de tipo de carta, en caso de no ser una carta numerada, pero habríamos
tenido que cambiar muchas partes del código, arriesgándonos a perder el tiempo por más errores.)
