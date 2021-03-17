#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

char* extender(char* numero, int sizeActual, int sizeObjetivo, int replace){
    
    char* newNumero = malloc((sizeObjetivo+2)*sizeof(char));
    memset(newNumero, 0, (sizeObjetivo+2)*sizeof(char));
    
    int index = 0;
    for (index = 0 ; index < (sizeObjetivo-sizeActual) ; index++)
        newNumero[index] = '0';
    strcat(newNumero, numero);
    
    if (replace == 1) free(numero);
    return newNumero;
}

char* suma(char* num1, char* num2, int size1, int size2, int permitirOverflow){
    int sizeMaximo = 0, flag1 = 0, flag2 = 0;
    
    if (size1 > size2){ // Se igualan en largo
        sizeMaximo = size1;
        num2 = extender(num2, size2, size1, 0);
        flag2 = 1;
    }else if (size2 > size1){
        sizeMaximo = size2;
        num1 = extender(num1, size1, size2, 0);
        flag1 = 1;
    }else sizeMaximo = size1;
    
    char* resultado1 = malloc((sizeMaximo+2)*sizeof(char));
    char* resultado2 = malloc((sizeMaximo+1)*sizeof(char));
    memset(resultado1, 0, sizeMaximo+2);
    memset(resultado2, 0, sizeMaximo+1);
    
    resultado1[sizeMaximo+1] = '\0';
    resultado2[sizeMaximo] = '\0';
    
    int i = 0, carry = 0, valor = 0;
    for (i = sizeMaximo; i > 0 ; i--){
        valor = ((int)num1[i-1]-48) + ((int)num2[i-1]-48) + carry;  // Se asignan los resultados para cada arreglo
        resultado1[i] = resultado2[i-1] = (char)(valor%2 + 48);
        carry = valor/2;
    }
    
    if (flag1 == 1) free(num1);
    if (flag2 == 1) free(num2);
    
    if (permitirOverflow == 0 || carry == 0){
        free(resultado1);
        return resultado2;
    }
    else{
        resultado1[0] = '1';
        free(resultado2);
        return resultado1;
    }
}

char* complemento(char* numero, int size){ // Retorna el complemento-2 de un numero
    int flag = 1, i;
    //printf("\nEntra: %s\n", numero);
    
    for (i = size ; i > 0 ; i--){
        if (flag == 1){
            if (numero[i-1] == '1') flag = 0;
        }else{
            if (numero[i-1] == '1') numero[i-1] = '0';
            else numero[i-1] = '1';
        }
        
    }
    //printf("Sale: %s\n", numero);
    return numero;
}


char* multiplicarG(char* numero1, char* numero2, int size1, int size2){
    //printf("Num1: %s\n", numero1);
    //printf("Num2: %s\n\n", numero2);
    
    int size, flag1 = 0, flag2 = 0;
    
    if (size1 > size2){ 
        numero2 = extender(numero2, size2, size1, 0);
        size = size1;
        flag2 = 1;
    }else if (size2 > size1){
        numero1 = extender(numero1, size1, size2, 0);
        size = size2;
        flag1 = 1;
    }else size = size1;
    // Se tienen ambos numeros del mismo largo
    
    if (size == 1){ // Caso de largo 1.
        char *resultado = malloc(10*sizeof(char));
        memset(resultado, 0, 10*sizeof(char));
        
        if (numero1[0] == '1' && numero2[0] == '1') resultado[0] = '1';
        else resultado[0] = '0';
        
        resultado[1] = '\0';
        return resultado;
    }
    
    char* xL = malloc(size*sizeof(char));  // Da igual que sobre memoria, de todas formas el string solo llega hasta la mitad
    char* xR = malloc(size*sizeof(char));
    char* yL = malloc(size*sizeof(char));
    char* yR = malloc(size*sizeof(char));
    memset(xL , 0, size*sizeof(char));
    memset(xR , 0, size*sizeof(char));
    memset(yL , 0, size*sizeof(char));
    memset(yR , 0, size*sizeof(char));
    
    
    int mitadL = size/2 + size % 2, mitadR = size/2;
    
    strncpy(xL, numero1, mitadL);   // Se asigna cada string a su respectiva mitad
    strncpy(xR, numero1+mitadL, mitadR);
    strncpy(yL, numero2, mitadL);
    strncpy(yR, numero2+mitadL, mitadR);
    //printf("xL: %s\nxR: %s\nyL: %s\nyR: %s\n\n", xL, xR, yL, yR);
    
    char *P1 = multiplicarG(xL, yL, mitadL, mitadL);
    char *P2 = multiplicarG(xR, yR, mitadR, mitadR);
    
    char *izq = suma(xL, xR, mitadL, mitadR, 1);
    char *der = suma(yL, yR, mitadL, mitadR, 1);
    
    //printf("izq: %s\nder: %s\n\n", izq, der);
    char *P3 = multiplicarG(izq, der, strlen(izq), strlen(der));
    //printf("P1:%s\nP2:%s\nP3:%s\n\n", P1, P2, P3);
      
    char* sumaP1P2 = suma(P1, P2, strlen(P1), strlen(P2), 1);
    int largoSuma = strlen(sumaP1P2);
    int largoP3 = strlen(P3);
    
    if (largoP3 > largoSuma){
        sumaP1P2 = extender(sumaP1P2, largoSuma, largoP3, 1);
        largoSuma = largoP3;
    }else if (largoSuma > largoP3){
        P3 = extender(P3, largoP3, largoSuma, 1);
        largoP3 = largoSuma;
    }
    
    //printf("P3: %s\n", P3);
    //printf("SumaP1P2: %s,   largo: %d\n", sumaP1P2, largoSuma);
    
    sumaP1P2 = complemento(sumaP1P2, largoSuma);
    //printf("Complemento: %s\n", comp);
    
    char *resta = suma(P3, sumaP1P2, largoP3, largoSuma, 0);
    int largoResta = strlen(resta);
  
    //printf("Resta: %s\n", resta);
    
    int largoP1 = strlen(P1);
    char* P1extendido = malloc(size*size*sizeof(char)); // Con memoria de m?s por si acaso
    char* RestaExtendida = malloc(size*size*sizeof(char));
    
    memset(P1extendido , 0, size*size*sizeof(char));
    memset(RestaExtendida , 0, size*size*sizeof(char));
    
    strncpy(P1extendido, P1, largoP1);
    strncpy(RestaExtendida, resta, largoResta);
    
    char *extension = malloc(size*sizeof(char));
    memset(extension, '0', size*sizeof(char));
   
    //printf("SIZE:%d\n", size);
    
    strncat(P1extendido, extension, 2*(size/2));
    strncat(RestaExtendida, extension, size/2);
    
    //printf("\nP1ex: %s\nRestaEx: %s\nP2: %s\n", P1extendido, RestaExtendida, P2);
    
    largoP1 = strlen(P1extendido);
    largoResta = strlen(RestaExtendida);
    
    if (largoP1 > largoResta){
        RestaExtendida = extender(RestaExtendida, largoResta, largoP1, 1);
        largoResta = largoP1;
    }else if (largoResta > largoP1){
        P1extendido = extender(P1extendido, largoP1, largoResta, 1);
        largoP1 = largoResta;
    }
    
    char* suma1 = suma(P1extendido, RestaExtendida, largoP1, largoResta, 1);
    char* suma2 = suma(suma1, P2, strlen(suma1), strlen(P2), 1);
    
    if (flag1 == 1) free(numero1);
    if (flag2 == 1) free(numero2);
    
    free(izq);
    free(der);
    free(P1);
    free(P2);
    free(P3);
    free(suma1);
    //free(suma2);
    free(P1extendido);
    free(RestaExtendida);
    free(extension);
    //free(comp);
    free(resta);
    free(sumaP1P2);
    free(xL);
    free(xR);
    free(yL);
    free(yR);
    
    return suma2;
}

void multiplicarC(int* numero1, int* numero2, int size){ // Multiplicaci?n en fuerza bruta

    int* resultado = malloc(size*2*sizeof(int));
    memset(resultado, 0, size*2*sizeof(int));
    
    //int parciales[size][size]; // Arreglo de arreglo. Se van guardando los datos de cada multiplicacion
    int* parciales = malloc(size*size*sizeof(int));
    memset(parciales, 0, size*size*sizeof(int));
    
    int index1, index2; // Indices que realizan las multiplicaciones
    
    for (index2 = size-1 ; index2 >= 0 ; index2--){
        for (index1 = size-1 ; index1 >= 0 ; index1--)
            parciales[(size-1-index2) + index1*size] = numero1[index1]*numero2[index2];
    } // Se tienen los resultados parciales de la multiplicacion. Por lo que ahora hay que sumarlos.
    
    int posicion = 2*size-1, valor;
    int carry = 0, temp2;
    
    for (index2 = size-1 ; index2 > 0-size ; index2--){ // itera por las columnas de la matriz, de derecha a izquierda
        valor = carry; // El valor inicia con la cantidad del carry anterior
                
        for (index1 = 0 ; index1 < size ; index1++){ //itera por las filas de la columna, de arriba a abajo
            temp2 = index2 + index1;
            
            if (temp2 < size && temp2 > -1)
                valor += parciales[index1+size*temp2];
            
            else if (temp2 > size-1) break;
        }
        resultado[posicion] = valor % 2;
        carry = valor / 2;
        posicion--;
    }
    
    if (carry == 1)
        resultado[posicion] = 1;
    else posicion++;
    
    // Imprimir la salida
    for (index1 = posicion; index1 < 2*size ; index1++)
            printf("%d", resultado[index1]);

    printf("\n");
    free(resultado);
    free(parciales);
}


// Recibe un arreglo de digitos y calcula el numero al que equivale
int calcularTotal(int* array, int size){
    int i = 0, total = 0;  
    for (i = 0; i < size; i++)
        total = 10 * total + array[i];
  
    return total;
}



int main() {
    char dato;
    int total, size = 0, digitos = 0, index;
    
    int *datos = malloc(32*sizeof(int)); // Tama?o para el numero de bits
    memset(datos, 0, 32*sizeof(dato));
    
    FILE* input = stdin; // Se abre el archivo de entrada.
    FILE* salida = fopen("resultado.txt", "w");
    
    while ((dato = fgetc(input)) != EOF){ // Itera sobre las distintas lineas de datos.
        
        //printf("dato leido = %c\n", dato);
        
        if (dato != '\n' && dato != ' '){ // Se ignoran los saltos de linea y espacios (por si acaso)
            total = 0;
            memset(datos, 0, 32*sizeof(dato));
            size = 0;
            digitos = 0;
            
            while(dato != ' '){  // Se lee hasta un espacio, de forma que se tiene el numero de bits.
                datos[digitos] = (int)dato -48;
                digitos++;
                dato = fgetc(input); // Lee el siguiente digito.
            }

            size = calcularTotal(datos, digitos);
            digitos = 0;

            int* numero1 = malloc(size*sizeof(int)); // Primer numero
            int* numero2 = malloc(size*sizeof(int)); // Segundo numero
            
            memset(numero1, 0, size*sizeof(int));
            memset(numero2, 0, size*sizeof(int));
            
            char *num1 = malloc((2+size)*sizeof(char));
            char *num2 = malloc((2+size)*sizeof(char));
            
            memset(num1, 0, (2+size)*sizeof(char));
            memset(num2, 0, (2+size)*sizeof(char));
            
            index = 0;
            while (index < size){ // se guardan los digitos del primer numero
                dato = fgetc(input);
                numero1[index] = (int)dato - 48;
                num1[index] = dato;
                index++;
            }
            num1[index] = '\0';

            dato = fgetc(input); // Se lee el espacio entre ambos numeros
            index = 0;
            while (index < size){ // se guardan los datos del segundo numero
                dato = fgetc(input);
                numero2[index] = (int)dato - 48;
                num2[index] = dato;
                index++;
            }
            num2[index] = '\0';
            
            fprintf(salida, "%d ", size); // Escribe el largo en el archivo de salida
            
            // Se realizan las multiplicaciones
            clock_t inicio = clock();
            
            char* fastMult = multiplicarG(num1, num2, size, size);
            printf("%s\n", fastMult);
            
            free(fastMult);
         
            clock_t multG = clock(); // Marca el tiempo que tarda en ejecutar la multiplicacion rapida
            
            multiplicarC(numero1, numero2, size);
                
            clock_t multC = clock(); // Marca el tiempo que tarda en ejecutar la multiplicacion lenta
            
            free(num1);
            free(num2);
            free(numero1);
            free(numero2);
            
            double ticks1 = (double)(multG - inicio); // Tiempo en Ticks de reloj
            double ticks2 = (double)(multC - multG); // Tiempo en Ticks de reloj
            double tiempo1 = ticks1 / CLOCKS_PER_SEC; // Tiempo en segundos
            double tiempo2 = ticks2 / CLOCKS_PER_SEC; // Tiempo en segundos
            printf("\n\n");
            fprintf(salida, "%f %f\n", tiempo1, tiempo2);
        }
    }
    free(datos);
    fclose(salida);
    return 0;
}

