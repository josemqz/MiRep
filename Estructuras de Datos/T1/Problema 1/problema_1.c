#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define aprobar 55 //Nota minima para aprobar


typedef struct {
    char sigla[7];
    int semestre; /*1er o 2do semestre*/
}curso;

typedef struct {
    char rolEstudiante[12];
    char siglaCurso[7];
    int nota;
}nota;

typedef struct {
    char rol[12], nombre[10], apellido[10];
    int fecha;
}alumno;

/*****
*   int verify
******
*   Funcion que verifica la correcta apertura de un archivo.
******
*   Input:
*       FILE *a : variable que apunta a un archivo
*       char *s : nombre del archivo
*        ......
******
*   Returns:
*       int, si el archivo no está vacío retorna el valor 0
*       NULL, se retorna en caso de fallar
*****/
int verify(FILE *a,char *s){
    if( a == NULL){
        printf("Archivo %s no pudo abrirse.\n", s);
        exit(1);
    }
    return 0;
}


/*****
*   int Archivo_Maestro
******
*   Obtiene la informacion de los structs obtenidos a partir de los archivos, para luego almacenar la informacion de
*   los alumnos que cumplen con los requisitos para estar en los archivos aprobados del primer y segundo semestre
******
*   Input:
*       int count        :   cantidad de lineas del archivo alumnos.
*       int* count2      :   cantidad de lineas del archivo notas.
*       int* count3      :   cantidad de lineas del archivo cursos.
*       nota** nota1     :   arreglo de punteros con los datos del archivo notas.
*       alumno** al1     :   arreglo de punteros con los datos del archivo alumnos.
*       curso** curso1   :   arreglo de punteros con los datos del archivo cursos.
*       int s            :   (buffer) string que almacena linea a escribir en el archivo.
*       FILE* arch_aprob :   puntero a archivo.
*     .........
******
*   Returns:
*       Retorna 0 si la funcion se ejecuta correctamente
*****/

int Archivo_Maestro(int count, int* count2, int* count3,
nota** nota1, alumno** al1,curso** curso1, int s, FILE* arch_aprob){
    int i,j,k;
    for (i = 0; i < count; i++) {
        char info[1000];
        sprintf(info,"%s %s %s",al1[i]->rol,al1[i]->nombre,al1[i]->apellido);
        //cantidad de ramos tomados por alumno
        int c = 0;
        //cantidad de ramos aprobados por alumno
        int d = 0;
        for (j = 0; j < *count2; j++) {
            for (k = 0; k < *count3; k++) {
                //comparar roles
                if(strcmp(al1[i]->rol,nota1[j]->rolEstudiante) == 0){
                    if(strcmp(nota1[j]->siglaCurso,curso1[k]->sigla) == 0 && curso1[k]->semestre == s){
                        c++;  //no pun intended
                        if(nota1[j]->nota >= aprobar){
                            d++;
                            sprintf(info, "%s %s %d", info, nota1[j]->siglaCurso, nota1[j]->nota);
                        }
                    }
                }
            }
        }
        if (c == d){
            fprintf(arch_aprob, info, sizeof(info));
            fprintf(arch_aprob, "\n");
        }
    }
    return 0;
}

int main() {
//variables de archivos
    FILE *alumnos, *notas, *cursos;
    FILE *aprobados1, *aprobados2;
//declaracion de structs
    nota **nota1;
    curso **curso1;
    alumno **al1;

//contadores
    int i;

//apertura de archivos
    alumnos = fopen("alumnos.txt","r");
    notas = fopen("notas.dat","r");
    cursos = fopen("cursos.dat","r");
//apertura de los archivos de salida
    aprobados1 = fopen("aprobados-s1.txt","w");
    aprobados2 = fopen("aprobados-s2.txt","w");

//comprobacion de la apertura exitosa
    verify(alumnos, (char*)"alumnos");
    verify(notas, (char*)"notas");
    verify(cursos,(char*)"cursos");
    verify(aprobados1,(char*)"aprobados-S1");
    verify(aprobados2,(char*)"aprobados-S2");

//obtencion de primeros caracteres para iteraciones
    int count = fgetc(alumnos) - 48;

    int *count2 = (int*)malloc(sizeof(int));
    fread(count2,sizeof(int), 1, notas);

    int *count3 = (int*)malloc(sizeof(int));
    fread(count3,sizeof(int), 1, cursos);

//asignacion de memoria a arreglos de punteros
    al1 = (alumno**)malloc(count * sizeof(alumno*));
    nota1 = (nota**)malloc(*count2 * sizeof(nota*));
    curso1 = (curso**)malloc(*count3 * sizeof(curso*));

//extraccion datos de alumnos.txt
    for (i = 0; i < count; i++) {
        al1[i] = (alumno*)malloc(count*sizeof(alumno*));
        fscanf(alumnos,"%s %s %s %d", al1[i]->rol, al1[i]->nombre, al1[i]->apellido, &al1[i]->fecha);
    }
//extraer datos de notas.dat
    for(i = 0; i < *count2; i++){
        nota1[i] = (nota*)malloc(*count2 * sizeof(nota));
        fread(nota1[i], sizeof(nota), 1, notas);
    }
 //extraer datos de cursos.dat
    for(i = 0; i < *count3; i++){
        curso1[i] = (curso*)malloc(*count3 * sizeof(curso));
        fread(curso1[i], sizeof(curso), 1, cursos);
    }

//append a archivo aprobados1
    Archivo_Maestro(count, count2, count3, nota1, al1, curso1, 1, aprobados1);
//append a archivo aprobados2
    Archivo_Maestro(count, count2, count3, nota1, al1, curso1, 2, aprobados2);

//liberacion de memoria
    for (i = 0; i < count; i++) {
        free(al1[i]);
    }
    for (i = 0; i < *count2; i++) {
        free(nota1[i]);
    }
    for (i = 0; i < *count3; i++) {
        free(curso1[i]);
    }
    free(count2);
    free(count3);

//cierre de archivos
    fclose(notas);
    fclose(cursos);
    fclose(alumnos);
    fclose(aprobados1);
    fclose(aprobados2);

    return 0;
}
