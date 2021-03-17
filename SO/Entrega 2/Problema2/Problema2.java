import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class MergeSort implements Runnable{
// Clase que se ejecuta utilizando threads. Utiliza la implementacion de la interfaz Runnable
    
    private static List<Integer> listaNumeros; // Todos los objetos de esta clase van a compartir la misma lista
    private final int izq; // Los indices son independientes para cada objeto 
    private final int der;    
    
    public MergeSort(List<Integer> lista, int izq, int der){
        MergeSort.listaNumeros = lista;
        this.izq = izq;
        this.der = der;
    } // Constructor de la clase, asigna los indices y el arreglo.
    
    public MergeSort(int izq, int der){
        this.izq = izq;
        this.der = der;
    } // Constructor secundario. Solo maneja los indices, porque el arreglo ya lo tienen los objetos subsecuentes.
    
    List<Integer> getLista(){ // Retorna el arreglo final. Solo lo usa el objeto base
        return MergeSort.listaNumeros;
    }
    
    
    void merge(List<Integer> lista, int izq, int med, int der){ // Funcion Merge. Recibe un arreglo y 3 indices con las posiciones
        int pos1 = med-izq+1, pos2 = der-med;

        int Izquierda[] = new int [pos1]; // Sub-arreglos temporales, para el ordenamiento
        int Derecha[] = new int [pos2];

        int index1;

        for (index1 = 0 ; index1 < pos1 ; index1++) Izquierda[index1] = lista.get(izq+index1); // Asigna los valores a los sub-arreglos
        for (index1 = 0 ; index1 < pos2 ; index1++) Derecha[index1] = lista.get(med+index1+1);

        index1 = 0;
        int index2 = 0, index3 = izq;
        
        // Index1 maneja a la lista Izquierda, index2 a Derecha e index3 a Array
        while((index1 < pos1) && (index2 < pos2)){ // Se van ordenando los valores mientras ambas listas tienen elementos
            if(Izquierda[index1] <= Derecha[index2]){ // Se copia el numero del arreglo izquierdo
                lista.set(index3, Izquierda[index1]);
                index1++;
            }
            else{
                lista.set(index3, Derecha[index2]); // Se copia el numero del arreglo derecho
                index2++;
            }
            index3++;
        }

        while(index1 < pos1){ // Si se acaban los elementos de la 2nda lista
            lista.set(index3,Izquierda[index1]);
            index1++;
            index3++;
        }

        while(index2 < pos2){ // Lo mismo pero para cuando solo quedan elementos en la lista 1.
            lista.set(index3, Derecha[index2]);
            index2++;
            index3++;
        }
    }

    // Funcion que recibe las listas y genera la division
    void mergeSort(List <Integer> lista, int izq, int der){
        if (izq < der){ // Si izq y derecha son iguales, no hay m?s lista.
            int medio = (izq+der)/2;

            MergeSort mitadIzq = new MergeSort(izq, medio); // Thread que maneja la mitad izquierda
            Thread t1 = new Thread(mitadIzq);
            t1.start();
            
            try{t1.join();} // Hace Join del thread
            catch(Exception ex){} // Except nada lel. Solo existe para que me deje hacer join
            
            MergeSort mitadDer = new MergeSort(medio+1, der); // Thread que maneja la mitad derecha
            Thread t2 = new Thread(mitadDer);
            t2.start();
            
            try{t2.join();}
            catch(Exception ex){} // Lo mismo pero con el thread 2
            
            merge(lista, izq, medio, der); // Se unen las 2 partes
        }
    }
    
    @Override
    public void run(){ // Ejecuta la funcion MergeSort con el arreglo recibido
        mergeSort(listaNumeros, izq, der);
    }
}

class Problema2{
    
    static void printLista(List <Integer> lista){ // Muestra los valores de la lista 
        for (int index = 0; index < lista.size(); index++){ 
            System.out.print(lista.get(index)); // Imprime los valores uno por uno
            System.out.print(" ");
        } 
        System.out.println("");
    }
    
    public static void main(String args[]) throws IOException{
        
        //Path archivo = Paths.get("input.txt"); // Abre el archivo input.txt
        List<Integer> Lista = new ArrayList<>();
        Scanner scan = new Scanner(new BufferedReader(new FileReader("input.txt")));
        
        while (scan.hasNext()){ // Se leen numeros desde el archivo input.txt
            if (scan.hasNextInt()) Lista.add(scan.nextInt());
            else scan.next(); // Lee cada numero separado por un espacio
        }
        
        System.out.print("Arreglo Ingresado: "); // Muestra el arreglo que se ingreso por texto
        printLista(Lista);

        MergeSort Ordenar = new MergeSort(Lista, 0, Lista.size()-1); // Crea una clase MergeSOrt
        Thread t = new Thread(Ordenar);
        t.start(); // Inicia el Thread con la clase Ordenar
        
        try{t.join();} // Le hace Join para esperar el resultadon
        catch(Exception ex){}// Le useless catch
    
        Lista = Ordenar.getLista(); // Obtiene la lista de la Clase
        Collections.reverse(Lista); // La invierte, asi a lo cochino
        
        System.out.print("Arreglo Resultante: ");
        printLista(Lista);
    }
}