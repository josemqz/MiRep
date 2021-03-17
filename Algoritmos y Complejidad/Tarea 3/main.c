#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clase{ // Una clase tiene un horario de inicio y uno de termino.
    int inicio;
    int termino;
} clase;

void printClases(clase *Clases, int cantidad){ // Printea una lista de clases
    int x = 0;
    printf("%d\n", cantidad);
    for (x = 0; x<cantidad; x++)
        printf("%d %d\n", Clases[x].inicio, Clases[x].termino);   
}

void merge(clase *Clases, int izq, int med, int der){  // Su mergesort lel
    int i, j, k; 
    int n1 = med - izq + 1; 
    int n2 =  der - med; 
    
    clase *L = malloc(n1*sizeof(clase)), *R = malloc(n2*sizeof(clase)); 
  
    for (i = 0; i < n1; i++)
        L[i] = Clases[izq+i];
    for (j = 0; j < n2; j++)
        R[j] = Clases[med+1+j];
  
    i = 0, j = 0, k = izq;
    while (i < n1 && j < n2){ 
        if (L[i].termino <= R[j].termino){ 
            Clases[k] = L[i]; 
            i++; 
        }else{ 
            Clases[k] = R[j]; 
            j++; 
        } 
        k++;
    }while (i < n1){ 
        Clases[k] = L[i]; 
        i++; 
        k++; 
    }while (j < n2){ 
        Clases[k] = R[j]; 
        j++; 
        k++; 
    }
    free(L);
    free(R);
} 

void mergeSort(clase* Clases, int izq, int der){ 
    if (izq < der){ 
        int med = izq+(der-izq)/2; 

        mergeSort(Clases, izq, med); 
        mergeSort(Clases, med+1, der);  
        merge(Clases, izq, med, der); 
    } 
} 

int topa(clase Clase1, clase Clase2){
    if ((Clase1.inicio >= Clase2.termino) || (Clase2.inicio >= Clase1.termino)) return 0; //Si una termina antes o cuando empieza la otra, no topan
    return 1; // Si no entra, deberian topar
}

int main() {
    int cantidadHorarios;    
    
    FILE* input = stdin; // Se abre el archivo de entrada standard.
    fscanf(input, "%d", &cantidadHorarios);
    
    if (!feof(input)){ // Itera sobre las distintas lineas de datos.
        
        if (cantidadHorarios == 0){ // Si no hay horarios se printea 0 y termina.
            fclose(input);
            printf("0\n");
            return 0;
        }
        
        clase *Clases = malloc(cantidadHorarios*sizeof(clase)); // Se crea el espacio para cada horario
        memset(Clases, 0, cantidadHorarios*sizeof(clase));
        
        int index = 0;
        for (index = 0 ; index < cantidadHorarios ; index++){
            fscanf(input, "%d", &(Clases[index].inicio));
            fscanf(input, "%d", &(Clases[index].termino));
        } // Se crea cada una de las clases.
        
        mergeSort(Clases, 0, cantidadHorarios-1); // Se usa MergeSort para ordenarlas segun hora de termino
        
        clase *Final = malloc(cantidadHorarios*sizeof(clase)); // Espacio para el resultado final.
        memset(Final, 0, cantidadHorarios*sizeof(clase));
        int Total = 0;
        
        //printClases(Clases, cantidadHorarios);
        
        int indexHorario = 0;
        for (index = 0; index < cantidadHorarios; index++){ // Se itera siempre seleccionando al horario que termina primero.
            if (indexHorario > (cantidadHorarios-1)) break; 
            
            Final[index] = Clases[indexHorario]; // Ya que est? ordenado, van del que termina primero al ultimo
            indexHorario++;
            Total++;
            for (indexHorario = indexHorario; indexHorario < cantidadHorarios; indexHorario++){
                if (topa(Final[index], Clases[indexHorario]) == 0) break; // Se omiten a todos los que topan con el seleccionado
            }
        }
        
        printClases(Final, Total); // Se muestran los horarios que se eligieron.
        free(Clases);
        free(Final);
    }
    fclose(input);
    return 0;
}