#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

char enter;
int orientacion = 0;
int nuevoColor = 99;

char color[5][10] = {"Negro", "Rojo", "Azul", "Verde", "Amarillo"};

typedef struct info{
    int players[4];
} info;


typedef struct mazo{
    char cartas[108][50];
    int n_cartas;
} mazo;


typedef struct jugada{
    int parametros[5];
    char carta[50];
} jugada;



// PIPES

int pipes[4][2], procesos[4] = {0,0,0,0};
char primeraCarta[50];

// Struct para el guardado de las cartas. Tiene espacio como para las 108 cartas del juego.

DIR *directorio;

/*
 Funcion Setup:  No recibe ni retorna nada.
 Genera el juego inicial, creando los directorios necesarios, junto con todas las cartas del mazo.
 Se utiliza un directorio general para todo el juego, que es la carpeta "Juego"
 */
void setup(){

    system("mkdir -p  Juego/Mazo");  // Directorio principal de las cartas
    system("mkdir -p Juego/Last"); // Directorio con la ultima carta jugada

    system("mkdir -p Juego/Jugadores/Jugador_1");  // Directorios con las manos de cada Jugador
    system("mkdir -p Juego/Jugadores/Jugador_2");
    system("mkdir -p Juego/Jugadores/Jugador_3");
    system("mkdir -p Juego/Jugadores/Jugador_4");


    FILE* carta;
    char *colorCarta[4] = {"Rojo", "Azul", "Verde", "Amarillo"};
    char buffer[35], numero, *tipoCarta[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "Salto", "Reversa"}; // 2 de cada color
    int color, tipo, cantidad;                                                                                        // el 0 sale solo 1 vez

    // En este ciclo se generan todas las cartas del mazo
    for (color = 0; color < 4; color++){
        for (cantidad = 0; cantidad < 2; cantidad++){ // Ciclo para generar todas las cartas duplicadas.
            for (tipo = 0; tipo < 12; tipo++){
                // La variable numero se utiliza para generar archivos iguales, ya que 2 archivos no pueden tener el mismo nombre
                // por lo tanto, se generan archivos del tipo ["NumCarta ColorCarta Repeticion]
                // como lo ser?a el caso de "1 Rojo 1" y "1 Rojo 2".
                numero = cantidad + '0';
                sprintf(buffer, "Juego/Mazo/%s %s %c.txt", tipoCarta[tipo], colorCarta[color], numero);
                carta = fopen(buffer, "w");
                fclose(carta);
                strcpy(buffer, "");
            }
        }

        // Los 0 se generan solo 1 para cada color, por lo que quedan en el ciclo de m?s afuera
        strcpy(buffer, "");
        sprintf(buffer, "Juego/Mazo/0 %s 0.txt", colorCarta[color]);
        carta = fopen(buffer, "w");
        fclose(carta);
        strcpy(buffer, "");

        // Las cartas +4 y comodines se crean 4 veces, pero sin ningun color.
        numero = color + '0';
        sprintf(buffer, "Juego/Mazo/+4 Negro %c.txt", numero);
        carta = fopen(buffer, "w");
        fclose(carta);
        strcpy(buffer, "");

        sprintf(buffer, "Juego/Mazo/Comodin Negro %c.txt", numero);
        carta = fopen(buffer, "w");
        fclose(carta);
        strcpy(buffer, "");
        }

    system("clear");

    puts("\n\n\t      __/\\\\\\________/\\\\\\__/\\\\\\\\______/\\\\\\_______/\\\\\\\\\\______        ");
    puts("\t       _\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\\\\\\\___\\/\\\\\\_____/\\\\\\///\\\\\\____       ");
    puts("\t        _\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\/\\\\\\__\\/\\\\\\___/\\\\\\/__\\///\\\\\\__      ");
    puts("\t         _\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\//\\\\\\_\\/\\\\\\__/\\\\\\______\\//\\\\\\_     ");
    puts("\t          _\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\\\//\\\\\\\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_    ");
    puts("\t           _\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_\\//\\\\\\/\\\\\\_\\//\\\\\\______/\\\\\\__   ");
    puts("\t            _\\//\\\\\\______/\\\\\\__\\/\\\\\\__\\//\\\\\\\\\\\\__\\///\\\\\\__/\\\\\\____  ");
    puts("\t             __\\///\\\\\\\\\\\\\\\\\\/___\\/\\\\\\___\\//\\\\\\\\\\____\\///\\\\\\\\\\/_____ ");
    puts("\t              ____\\/////////_____\\///_____\\/////_______\\/////_______");

    puts("\n\n\t\t\t\t\t\t.");
    sleep(1);
    puts("\t\t\t\t\t\t.");
    sleep(1);
    puts("\t\t\t\t\t\t.");
    sleep(0.5);
    printf("\n\t\t\t *** Se han creado 108 cartas en el mazo ***\n\n");
    sleep(0.5);
    }


mazo* leerMazo(){
    // Se leen todas las cartas dentro del directorio Mazo

    mazo *Mazo = malloc(sizeof(mazo));
    memset(Mazo, 0, sizeof(mazo));

    struct dirent *dir;

    int count = 0;
    directorio = opendir("Juego/Mazo/.");
    // se revisan todos los archivos bajo el directorio Juego/Mazo/

    if (directorio){
        while ((dir = readdir(directorio)) != NULL){
            if ((strcmp(dir->d_name, ".") != 0 && (strcmp(dir->d_name, "..") != 0))){
                strcpy(Mazo->cartas[count],dir->d_name);
                count++;
                // Se anaden en el struct, recibiendo un indice entre [0-108]
            }
        }
        Mazo->n_cartas = count;
        closedir(directorio);
    }
    return Mazo;
}


//elimina .txt de nombre de archivo
char* sintxt(char* cartaFile){

    char *nombreCarta = malloc(50*sizeof(char));                                //MALLOC
    memset(nombreCarta, 0, 50*sizeof(char));

    char tmp1[50] = "";
    char tmp2[50] = "";

    sscanf(cartaFile, "%s %s %s.txt",nombreCarta, tmp1, tmp2);

    sprintf(nombreCarta,"%s %s %c", nombreCarta, tmp1, tmp2[0]);

    return nombreCarta;
}


//Elimina el numero de repeticion de carta
char* limpiarFormato(char* nombre){

    char tmp1[20], tmp2[20], tmp3[5];
    sscanf(nombre, "%s %s %s", tmp1, tmp2, tmp3);
    sprintf(nombre, "%s %s", tmp1, tmp2);

    return nombre;
}


int esDigito(char* P){
    int i;
    for(i = 0; P[i]; i++){
        if(P[i] < '0' || P[i] > '9'){
            return 0;
        }
    }
    return 1;
}


//recibe el nombre de una carta (numero + color + numero de copia de archivo) y
//retorna un string con un numero de 4 digitos que indica informacion
//relevante (color + tipo carta + numero + orientacion)
char* analizarCarta(char* carta){

    //ncartas : 0 = dont care, 1 = tiene 1 carta, 2 = ganó
    //tipo carta : 0 = numero, 1 = reversa, 2 = comodin, 3 = bloqueo, 4 = +2, 5 = +4
    //color : 0 = negro, 1 = rojo, 2 = azul, 3 = verde, 4 = amarillo


    //se separan los elementos del string carta
    char datosCarta[2][50] = {"",""};
    char basura[10] = "";

    sscanf(carta, "%s %s %s", datosCarta[0], datosCarta[1], basura);

    //se interpretan los valores obtenidos
    int analisis = 0;
    char tipoCarta[6][10] = {"Numero", "Reversa", "Comodin", "Salto", "+2", "+4"};


    //tipo carta
    int i;
    for (i = 0; i < 6; i++){
        if (strcmp(datosCarta[0], tipoCarta[i]) == 0){
            analisis += i * 100;
            break;
        }
    }

    //tipo carta == numero
    if (esDigito(datosCarta[0])){
        analisis += ((int)datosCarta[0][0] - 48) * 10;
    }

    //color
    for (i = 0; i < 5; i++){
        if (strcmp(datosCarta[1],color[i]) == 0){
            analisis += i * 1000;
        }
    }

    //orientacion
    if (strcmp(datosCarta[0], tipoCarta[1]) == 0){
        analisis += 1;
    }


//int -> str
    char *analisisStr = malloc(5*sizeof(char));                                 //MALLOC
    memset(analisisStr, 0, 5*sizeof(char));

    int modulo = 1000, index = 0;

    while (index < 4){
        analisisStr[index] = (analisis/modulo) + '0';
        analisis %= modulo;
        modulo /= 10;
        index++;
    }
    analisisStr[4] = '\0';


//se agrega una letra al tercer digito del analisis
//en caso de no ser una carta enumerada
    if(analisisStr[1] != '0'){
        for (i = 0; i < 6; i++){
            if (strcmp(datosCarta[0], tipoCarta[i]) == 0){
                analisisStr[2] = 'a' + i;
                break;
            }
        }
    }

    return analisisStr;
}


//carta random de mazo a jugador/Last. Retorna el nombre de la carta
char* randPull(mazo* Mazo, int opcion, int jugador){

    time_t t;
    srand((unsigned) time(&t));

    int r = rand() % Mazo->n_cartas;

    char comm[100] = "mv Juego/Mazo/'";
    char strJ[2] = "";
    *strJ = jugador + '0';

    strcpy(primeraCarta, Mazo->cartas[r]);
    strcat(comm, Mazo->cartas[r]);
    strcat(comm, "'");

//retorna informacion de carta
    char* nombreCarta = sintxt(Mazo->cartas[r]);

//se reemplaza carta sacada por ultima en arreglo
    if (r != Mazo->n_cartas - 1){
    strcpy(Mazo->cartas[r], Mazo->cartas[Mazo->n_cartas-1]);
    }

    Mazo->n_cartas = Mazo->n_cartas - 1;

    switch(opcion) {
        case 0:
            strcat(comm, " Juego/Jugadores/Jugador_");
            strcat(comm, strJ);
            break;

        case 1:
            system("rm -f Juego/Last/*");
            strcat(comm, " Juego/Last");
            break;

        default:
            puts("Opcion invalida"); //no deberia pasar nunca
    }
    system(comm);
    return nombreCarta;
}


//Jugador pone carta en monton
void pushCarta(mazo* Mano, int cartaIndex, int jugador){

    system("rm -f Juego/Last/*");

    char comm[200] = "mv 'Juego/Jugadores/Jugador_";
    char player[2] = {jugador + '0','\0'};

    sprintf(comm, "%s%s/%s.txt' Juego/Last", comm, player, Mano->cartas[cartaIndex]);

    system(comm);
}


int next(int jugador, int caso){

    int siguienteJugador;

    switch(caso){

        //normal
        case 0:
            if (orientacion == 0){
                if (jugador == 4) siguienteJugador = 1;
                else siguienteJugador = jugador + 1;
            }

            else{
                if (jugador == 1) siguienteJugador = 4;
                else siguienteJugador = jugador - 1;
            }
            break;

        //salto
        case 1:
            if (orientacion == 0){
                if (jugador < 3) siguienteJugador = jugador + 2;
                else if (jugador == 3) siguienteJugador = 1;
                else siguienteJugador = 2;
            }

            else{
                if (jugador > 2) siguienteJugador = jugador - 2;
                else if (jugador == 2) siguienteJugador = 4;
                else siguienteJugador = 3;
            }
            break;

        //reversa
        case 2:
            if (orientacion == 0){
                orientacion = -1;

                if (jugador > 1) siguienteJugador = jugador - 1;
                else if (jugador == 1) siguienteJugador = 4;
                else siguienteJugador = 1;
            }

            else{
                orientacion = 0;

                if (jugador == 4) siguienteJugador = 1;
                else siguienteJugador = jugador + 1;
            }
            break;

    }

    return siguienteJugador;

}


//comprueba que la carta jugada cumpla con las condiciones del juego
//se retorna el siguiente jugador correspondiente
int jugadaValida(mazo* Mazo, int jugador, char* cartaDatos, char* LastDatos){

    int siguienteJugador;

    //negra
    if (cartaDatos[0] == '0'){

        if (jugador != 0){                  //en caso que a jugador 0 le salga, el 1 pone cualquier carta

            int valido = -1;
            while (valido == -1){

                valido = 0;

                puts("\n *** Elegir nuevo color ***\n");

                int i;
                for(i = 1; i < 5; i++){
                        printf("[%d] %s\n", i, color[i]);
                }

                scanf(" %d", &nuevoColor);
                if (nuevoColor < 1 || nuevoColor > 4){
                    valido = -1;
                }
            }
        }

        //+4
        if (cartaDatos[1] == '5'){
            int c;
            if (Mazo->n_cartas > 3){
                for (c = 0; c < 4; c++){
                        free(randPull(Mazo, 0, next(jugador,0)));
                }
            }
            else {
                for (c = 0; c < Mazo->n_cartas; c++){
                    free(randPull(Mazo, 0, next(jugador,0)));
                }
            }

            siguienteJugador = next(jugador, 1);

        }

        //comodin
        else if (cartaDatos[1] == '2'){
            //no pasa nada en realidad jsj
            siguienteJugador = next(jugador, 0);
        }

        return siguienteJugador;
    }


//infoCarta = color + tipo carta + numero + orientacion
//tipo carta : 0 = numero, 1 = reversa, 2 = comodin, 3 = bloqueo, 4 = +2, 5 = +4
//color : 0 = negro, 1 = rojo, 2 = azul, 3 = verde, 4 = amarillo

//Si se pone una carta que no cumpla esto, se debe robar una carta.
    //colores o numero
    else if (cartaDatos[0] == LastDatos[0] ||                           //color
            cartaDatos[2] == LastDatos[2] ||                            //numero
            (LastDatos[0] == '0' && (int)cartaDatos[0]-48 == nuevoColor) || //ultima carta comodin
            (LastDatos[0] == '0' && nuevoColor == 99)) {                //si primera carta del juego es negra

        //Reversa
        if (cartaDatos[1] == '1'){
            siguienteJugador = next(jugador, 2);
        }

        //Bloqueo
        else if (cartaDatos[1] == '3'){
             siguienteJugador = next(jugador, 1);
         }

        //+2
        else if (cartaDatos[1] == '4'){

            if (Mazo->n_cartas > 1){
                int c;
                for (c = 0; c < 2; c++){
                    free(randPull(Mazo, 0, next(jugador,0)));
                }
            }

            else {
                free(randPull(Mazo, 0, next(jugador,0)));
            }

            siguienteJugador = next(jugador, 1);
        }

        else{
             siguienteJugador = next(jugador, 0);
        }

        return siguienteJugador;
    }

    else return -1;
}


jugada* Jugar(char *cartaLast, int jugador, mazo* Mazo){

    //infoCarta = color + tipo carta + numero + orientacion
    //tipo carta : 0 = numero, 1 = reversa, 2 = comodin, 3 = bloqueo, 4 = +2, 5 = +4
    //color : 0 = negro, 1 = rojo, 2 = azul, 3 = verde, 4 = amarillo

    int siguienteJugador = 999;
//mano de jugador actual
    mazo* Mano = malloc(sizeof(mazo));
    memset(Mano, 0, sizeof(mazo));
//struct a retornar

    jugada* J = malloc(sizeof(jugada));
    memset(J, 0, sizeof(jugada));

    strcpy(J->carta, cartaLast);

    //analisis ultima jugada
    char *LastDatos = analizarCarta(cartaLast);

    cartaLast = limpiarFormato(cartaLast);


    if (jugador == 0){
        siguienteJugador = jugadaValida(Mazo, 0, LastDatos, LastDatos);

        free(LastDatos);
        free(Mano);

        if (orientacion == 0){
            J->parametros[0] = 1;
            J->parametros[1] = siguienteJugador;
        }
        else{
            J->parametros[0] = 4;
            J->parametros[1] = siguienteJugador;
        }
        return J;
    }


    puts("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    printf(" JUGADOR %d |\n", jugador);
    puts(" ---------");
    printf("\nUltima jugada: \n%s\n\n", cartaLast);

    if(LastDatos[0] == '0' && nuevoColor != 99){
        printf("Nuevo color: %s\n\n", color[nuevoColor]);
    }


    struct dirent *dir;
    char dirMano[100] = "Juego/Jugadores/Jugador_", strJ[2] = "";
    *strJ = jugador + '0';      //jugador de int a string

    strcat(dirMano, strJ);
    directorio = opendir(dirMano);

//imprimir cartas de la mano y registrarlas en arreglo
    int i = 0;
    if (directorio){
        while ((dir = readdir(directorio)) != NULL){
            if ((strcmp(dir->d_name, ".") != 0 && (strcmp(dir->d_name, "..") != 0))){

                char* nombreCarta = sintxt(dir->d_name);    //eliminar .txt
                strcpy(Mano->cartas[i], nombreCarta);

                nombreCarta = limpiarFormato(nombreCarta);
                printf(" [%d] %s\n", i, nombreCarta);

                free(nombreCarta);
                i++;
            }
        }
    }

    closedir(directorio);
    Mano->n_cartas = i;

    printf(" [%d] %s\n", i, "Sacar de mazo");
    printf(" [%d] %s\n", i + 1, "Pasar");
    puts("\n *** ELEGIR CARTA (segun indice) ***");

    int opcion, opcionValida = 0;
    scanf(" %d", &opcion);

    int siguienteTmp;
    while(opcionValida == 0){

        opcionValida = 1;

        if(opcion == i + 1){

            free(LastDatos);
        }

        else if (opcion == i){

            char* cartaPull = randPull(Mazo, 0, jugador);
            strcpy(Mano->cartas[i],"");
            strcpy(Mano->cartas[i], cartaPull);

            char* cartaDatos = analizarCarta(cartaPull);
            Mano->n_cartas += 1;

            cartaPull = limpiarFormato(cartaPull);
            printf("\n *** Sacando de mazo... ***\n%s\n\n", cartaPull);

            siguienteTmp = jugadaValida(Mazo, jugador, cartaDatos, LastDatos);


            if (siguienteTmp == -1) {
                //pasa el turno
                puts(" *** No se puede jugar la carta ***");
                sleep(1);
            }

            else{
                siguienteJugador = siguienteTmp;

                puts("\n *** Se juega la carta ***");
                sleep(1);

                Mano->n_cartas -=1;
                strcpy(J->carta, Mano->cartas[opcion]);
            }

            free(cartaDatos);
            free(cartaPull);
            free(LastDatos);
        }


        else if (opcion >= 0 && opcion < i){

            char* cartaDatos = analizarCarta(Mano->cartas[opcion]);
            Mano->n_cartas -= 1;

            strcpy(J->carta, Mano->cartas[opcion]);

            siguienteTmp = jugadaValida(Mazo, jugador, cartaDatos, LastDatos);

            if (siguienteTmp == -1) {

                puts("\n *** Jugada no permitida. Se debe sacar otra carta del mazo ***\n");
                sleep(1);

                char* cartaPull = randPull(Mazo, 0, jugador);
                strcpy(Mano->cartas[Mano->n_cartas], cartaPull);
                Mano->n_cartas += 1;

                cartaPull = limpiarFormato(cartaPull);
                printf(" *** Sacando de mazo... ***\n%s\n ", cartaPull);

                free(cartaPull);
            }

            else{
                puts(" *** Se juega la carta ***");

                char* tmp = malloc(50 * sizeof(char));
                memset(tmp, 0, 50*sizeof(char));

                strcpy(tmp, Mano->cartas[opcion]);
                tmp = limpiarFormato(tmp);
                printf("%s\n", tmp);
                free(tmp);

                siguienteJugador = siguienteTmp;

            }
            free(cartaDatos);
            free(LastDatos);

        }

        else{


            for (i = 0; i < Mano->n_cartas; i++){
                printf(" [%d] %s\n", i, Mano->cartas[i]);
            }

            printf(" [%d] %s\n", i, "Sacar de mazo");
            printf(" [%d] %s\n", i + 1, "Pasar");
            printf("\nUltima jugada: \n%s\n", cartaLast);
            puts("\nOpcion invalida");

            opcionValida = 0;

            puts("Elegir opcion");
            scanf(" %d", &opcion);
        }
    }


//se pone la carta en monton
    if (opcion != i + 1 && siguienteTmp != -1){
        pushCarta(Mano, opcion, jugador);
    }

    if (siguienteJugador == 999){
        siguienteJugador = jugador + 2*orientacion + 1;
        if (siguienteJugador == 5) siguienteJugador = 1;
        else if (siguienteJugador == 0) siguienteJugador = 4;
    }

    if (Mano->n_cartas > 1) J->parametros[0] = 0;
    else if (Mano->n_cartas == 1) J->parametros[0] = 1;
    else if (Mano->n_cartas == 0) J->parametros[0] = 2;

    J->parametros[1] = siguienteJugador;

    free(Mano);
    puts("\n\n");
    return J;
}


// Funcion de Juego del Player 1
void jugadorPrincipal(mazo *Mazo){  // Funcion que controla al proceso Padre

    // Debe hacer la primera jugadada de la partida, e indicar los resultados

    char *primera = sintxt(primeraCarta);  // Lee la primera carta que hay en el maso (guardada como global porque soy asi de penca))
    jugada *Jugada = Jugar(primera, 0, Mazo);  // Realiza una jugada "fantasma" utilizando al jugador 0, es decir, aplica las

    free(primera);

    // reglas correspondientes para la carta que se coloca en el pozo.
    info *Info = malloc(sizeof(info));
    memset(Info, 0, sizeof(info));

    int index = 0;
    for (index = 0; index < 4; index++){        // Se crea el struct info y se inicializa con 0;
        Info->players[index] = 0;
    }

//  Realiza una "jugada fantasma" con la carta que se coloca en el pozo al azar al comienzo de la partida
//  Esto porque si la primera carta salta el turno del jugador 1, se debe comenzar con otro jugador.

    int proxJugador = Jugada->parametros[1];
    int jugadorActual = 0, jugadores = 0;

    // Se obtiene a que jugador le toca el primer turno, y se ejecuta la funcion como es de esperarse.

    int enPartida = 1;

            // Los structs Jugada e Info contienen informacion relevante para coordinar las jugadas.
        // Info permite indicar a que jugadores les queda 1 carta, mas de 1, o ya ganaron.
            // Jugada contiene 3 parametros. Cantidad de cartas (>1, 1 o 0), a quien le toca el siguiente turno
        // Y el string con la ultima carta que se jugo.

            // Awante mandar structs por pipes c:  esta muy util

    int *jugando = malloc(sizeof(int)), *recibiendo = malloc(sizeof(int)), iWin = 0;
    memset(jugando, 0, sizeof(1));
    memset(recibiendo, 0, sizeof(int));

    char carta[50];
    strcpy(carta, ""); // Se mantiene la carta jugada en un arreglo, porque se necesita guardar antes de liberar
    jugando[0] = 1;

    if (proxJugador == 1) recibiendo[0] = 0;
    else recibiendo[0] = 1;

    while (enPartida == 1){

        if (proxJugador != 1){   // El caso en el que el turno es de otro jugador

            jugadorActual = Jugada->parametros[1];

            Jugada->parametros[4] = nuevoColor;
            Jugada->parametros[3] = orientacion; // Se guarda la orientacion actual del juego, para enviarselo al siguiente proceso.

            if (recibiendo[0] != 2){
                write(pipes[proxJugador-1][1], jugando, sizeof(int));
                write(pipes[proxJugador-1][1], Jugada, sizeof(jugada));
                write(pipes[proxJugador-1][1], Mazo, sizeof(mazo));
                write(pipes[proxJugador-1][1], Info, sizeof(info));
                // Se envian todos los struct con informacion al jugador
                // Estos structs se envian por pipe, y son recibidas por el siguiente jugador.
                recibiendo[0] = 1;
            }
            while (recibiendo[0] != 0){
                if (recibiendo[0] == 1){
                    read(pipes[0][0], recibiendo, sizeof(int));
                    iWin = 0;
                    // Se mantiene en un loop "en espera", y asi evita seguir ejecutandose hasta que los hijos esten listos.
                    // Se puede recibir 0 o 2.
                        // Con 0 se termina el loop de espera, y se continua la ejecucion normal del juego
                        // Con 2 se transmite que alguien ha ganado, terminando el programa y limpiando todo.
                }

                if (recibiendo[0] == 2){  // Se utiliza if por si el estado cambia en el read anterior.

                    if (iWin == 0){
                        read(pipes[0][0], Info, sizeof(info));
                        read(pipes[0][0], Mazo, sizeof(Mazo));
                    }

                    int ganador = 99;

                    for (jugadores = 1 ; jugadores < 4 ; jugadores++){
                        if (Info->players[jugadores] == 2){
                            printf("P1: Ha ganado el jugador %d!\n", jugadores+1);
                            ganador = jugadores+1;
                        }
                    }

                    if (Info->players[0] == 2){
                        printf("P1: He ganado!\n");
                        ganador = 1;
                    }

                    else if (Mazo->n_cartas < 1 || ganador == 99)
                        printf("P1: El mazo se quedo sin cartas!.\n");

                    // Mensaje de que el juego termino, enviado a todos los procesos hijos.
                    write(pipes[1][1], recibiendo, sizeof(int));
                    write(pipes[2][1], recibiendo, sizeof(int));
                    write(pipes[3][1], recibiendo, sizeof(int));

                    // Mensaje de quien gano
                    recibiendo[0] = ganador;
                    write(pipes[1][1], recibiendo, sizeof(int));
                    write(pipes[2][1], recibiendo, sizeof(int));
                    write(pipes[3][1], recibiendo, sizeof(int));

                    //Damnatio ad metalla, free a todo y fin del programa
                    free(jugando);
                    free(recibiendo);
                    free(Jugada);
                    free(Mazo);
                    free(Info);
                    exit(1);
                }
            }

            // En caso de que el juego continue, se sigue como si nada, leyendo los datos necesarios para continuar
            read(pipes[0][0], Jugada, sizeof(jugada));
            read(pipes[0][0], Mazo, sizeof(mazo));
            read(pipes[0][0], Info, sizeof(info));


            Info->players[jugadorActual-1] = Jugada->parametros[0];
            Jugada->parametros[2] = jugadorActual;
            proxJugador = Jugada->parametros[1];
            orientacion = Jugada->parametros[3];
            nuevoColor = Jugada->parametros[4];
            // Se lee la orientacion, el proximo jugador y se continua con la sigueinte ronda.
        }

        else{  // Le toca jugar al jugador 1.


            if (Info->players[0] == 1)
                printf("P1: Solo tengo una carta!\n");
                        // Primero revisa si le queda una sola carta
            for (jugadores = 1 ; jugadores < 4 ; jugadores++){
                if(Info->players[jugadores] == 1)
                    printf("P1: El jugador %d tiene 1 sola carta!\n", jugadores+1);
            }
                        // Revisa si a alguien mas le queda solo una carta

            jugadorActual = Jugada->parametros[1];

            strcpy(carta, Jugada->carta);

            free(Jugada);  // Libera el espacio de la jugada anterior, aceptando la nueva.

            Jugada = Jugar(carta, 1, Mazo);
            Info->players[0] = Jugada->parametros[0]; // Se realiza la jugada y se asigna el nivel de cartas del jugador 1
                                                      // 2: Sin cartas ; 1: Una sola carta ; 0: Ninguna anterior.

            if (Info->players[0] == 2){  // Revisa en caso de que se haya quedado sin cartas.
                recibiendo[0] = 2;      // De ser asi, itera nuevamente pero va directamente a avisar a los demas.
                iWin = 1;
            }

            if (Mazo->n_cartas < 1){  // Si el mazo queda vac?o luego de la jugada, debe terminar
                recibiendo[0] = 2;
                iWin = 2;
            }

            Jugada->parametros[4] = nuevoColor;
            Jugada->parametros[3] = orientacion;
            Jugada->parametros[2] = jugadorActual;
            proxJugador = Jugada->parametros[1];
        }
    }
}


// Funcion de juego de los procesos hijos
// No tiene tanto comentario porque es similar a lo del padre
void jugadorPC(){
    int jugadores = 0, pipeJugador = 0; // Numero del pipe que se comunica con el Padre, y variable utilizada en lectura.

    if (getpid() == procesos[1]) pipeJugador = 1;   // Obtiene el numero del pipe que utiliza para recibir mensajes del padre
    else if (getpid() == procesos[2]) pipeJugador = 2;
    else if (getpid() == procesos[3]) pipeJugador = 3;


    int enPartida = 1, *play = malloc(sizeof(int)), *sent = malloc(sizeof(int));
    memset(play, 0, sizeof(int)); // 2 numeros dinamicos, utilizados para coordinacion entre procesos por uso de pipes.
    memset(sent, 0, sizeof(int));

    char carta[50] = ""; // Se mantiene la carta jugada en un arreglo, porque se necesita guardar antes de liberar

    while (enPartida == 1){

        if (play[0] == 1){  // "play" define si es momento de jugar. De no serlo, continua esperando.


            jugada *Jugada = malloc(sizeof(jugada));
            mazo *Mazo = malloc(sizeof(mazo));
            info *Info = malloc(sizeof(info));

            memset(Jugada, 0, sizeof(jugada));
            memset(Mazo, 0, sizeof(mazo));
            memset(Info, 0, sizeof(info));

            // Asigna el espacio necesario para la informacion entregada por Pipes, y luego lee si casilla del pipe, donde la obtiene.

            read(pipes[pipeJugador][0], Jugada, sizeof(jugada)); // Recibe la informacion enviada por el padre
            read(pipes[pipeJugador][0],   Mazo, sizeof(mazo));
            read(pipes[pipeJugador][0],   Info, sizeof(info));

            nuevoColor = Jugada->parametros[4];
            orientacion = Jugada->parametros[3]; // Copia el sentido actual de la orientacion.

            for (jugadores = 0 ; jugadores < 4 ; jugadores++){
                      // Se revisa el estado actual de las cartas de todos los jugadores.

                if((Info->players[jugadores] == 1) && (jugadores != pipeJugador))
                    printf("P%d: El jugador %d tiene 1 sola carta!\n", pipeJugador+1, jugadores+1);

                else if (Info->players[jugadores] == 1 && jugadores == pipeJugador)
                    printf("P%d: Tengo solo una carta!\n", pipeJugador+1);
            }


            strcpy(carta, Jugada->carta);
            free(Jugada); // Se necesita pasar como parametro la carta, y a la vez liberar la memoria del struct
                          // por lo que se guarda la carta actual en una variable del proceso.

            Jugada = Jugar(carta, pipeJugador + 1, Mazo);

            Jugada->parametros[4] = nuevoColor;
            Jugada->parametros[3] = orientacion;
            Info->players[pipeJugador] = Jugada->parametros[0];

            // Realiza su jugada y le informa toda la informacion correspondiente al proceso padre.

            if (Jugada->parametros[0] == 2){
                sent[0] = 2;
                write(pipes[0][1], sent, sizeof(int));
                write(pipes[0][1], Info, sizeof(info));
                write(pipes[0][1], Mazo, sizeof(mazo));

                free(Info);
                free(Jugada);
                free(Mazo);
                play[0] = 0;
            }

            else if (Mazo->n_cartas < 1){
                sent [0] = 2;
                write(pipes[0][1], sent, sizeof(int));
                write(pipes[0][1], Info, sizeof(info));
                write(pipes[0][1], Mazo, sizeof(mazo));

                free(Info);
                free(Jugada);
                free(Mazo);
                play[0] = 0;
            }

            else{
                write(pipes[0][1], sent, sizeof(int));
                write(pipes[0][1], Jugada, sizeof(jugada));
                write(pipes[0][1], Mazo, sizeof(mazo));
                write(pipes[0][1], Info, sizeof(info));

                free(Info);
                free(Jugada);   // Libera todos sus datos "temporales"
                free(Mazo);
                play[0] = 0;
            }
        }
        else{
            read(pipes[pipeJugador][0], play, sizeof(int));

            if (play[0] == 2){

                read(pipes[pipeJugador][0], play, sizeof(int));

                if (play[0] != 99){
                    if (play[0] != pipeJugador+1)
                        printf("P%d: Ha ganado el jugador %d!\n", pipeJugador+1, play[0]);
                    else if (play[0] == pipeJugador+1)
                        printf("P%d: He ganado!\n", pipeJugador+1);
                }
                else if (play[0] == 99)
                    printf("P%d: El mazo se quedo sin cartas!.\n", pipeJugador+1);

                free(play);
                free(sent);
                exit(1);
            }
        }
    }
}



int main(){

    int restaurar = 0, jugador, carta, index;


    for (index = 0 ; index < 4 ; index++){
        pipe(pipes[index]);
    }

    if (restaurar != 1){
        directorio = opendir("Juego");
        if (directorio) system("rm -r Juego");
        setup();
    }
    closedir(directorio);

    mazo *Mazo = leerMazo();

    // Se asignan las cartas a las manos de cada jugador.
    for(jugador = 1; jugador <= 4; jugador++){
        for(carta = 0; carta < 7; carta++){
            free(randPull(Mazo, 0, jugador));
        }
    }

    printf("\n\t***  Se le han asignado 7 cartas a cada jugador, y se ha colocado una en el pozo ***\n\n\n");
    sleep(1);

    //pozo
    free(randPull(Mazo, 1, -1));

    int proceso, contador;  // Se crea un array para los PIDs de cada uno de los procesos
    procesos[0] = getpid(); // la primera posicion del arreglo es el PID del padre

    for (contador = 0 ; contador < 3 ; contador++){
        proceso = fork();
        if (proceso == 0){
            procesos[contador+1] = getpid();
            break;
        }
        else procesos[contador+1] = proceso;
    }

    // CONFIGURACION DE PIPES
    /*

     Se utilizan 4 pipes, guardados en un arreglo global, llamados Pipes[0], ... , Pipes[3]

     Todos los hijos escriben en Pipes[0], y el padre solo lee ese
     Ademas, el padre posee un 3 pipes, con los que se comunica con los 3 hijos Pipe1: P-h1, Pipe2: P-h2, Pipe3: P-h3

    */
    if (getpid() == procesos[0]){   // Cierra los pipes que el padre no utiliza.
        for (index = 1; index < 4 ; index++) close(pipes[index][0]);
        close(pipes[0][1]);
    }

    else if (getpid() == procesos[1]){  // Cierra los pipes que el hijo 1 no utiliza
        for (index = 0 ; index < 4 ; index++){
            if (index == 0) close(pipes[0][0]);
            else if (index == 1) close(pipes[1][1]);
            else{
                close(pipes[index][0]);
                close(pipes[index][1]);
            }
        }
    }

    else if (getpid() == procesos[2]){ // Cierra los pipes que el hijo 2 no utiliza
        for (index = 0 ; index < 4 ; index++){
            if (index == 0) close(pipes[0][0]);
            else if (index == 2) close(pipes[2][1]);
            else{
                close(pipes[index][0]);
                close(pipes[index][1]);
            }
        }
    }

    else if (getpid() == procesos[3]){  // Cierra los pipes que el hijo 3 no utiliza
        for (index = 0 ; index < 4 ; index++){
            if (index == 0) close(pipes[0][0]);
            else if (index == 3) close(pipes[3][1]);
            else{
                close(pipes[index][0]);
                close(pipes[index][1]);
            }
        }
    }

    // El padre se envia a la funcion jugadorPrincipal
    if (getpid() == procesos[0]){
        jugadorPrincipal(Mazo);
    }
    // Cada uno de los hijos se envian a jugadorPC
    else{
        free(Mazo);
        jugadorPC();
    }
    //terminarPartida();
    return 0;
}
