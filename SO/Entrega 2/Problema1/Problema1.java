import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Funcion{
    char letra; // Letra con la que se identifica a la funcion;
    String funcion[];
    
    public Funcion(char letra, String funcion[]){
        this.letra = letra;
        this.funcion = funcion;
    }
}

class Resolucion implements Runnable{
    
    List<Funcion> Funciones;
    String variable; // El valor que se le da a la variable
    char funcion; // la funcion que se utiliza
    String resultado;
    
    
    public Resolucion(List <Funcion> Funciones, String Entrada){
        this.Funciones = Funciones;
        this.funcion = Entrada.charAt(0);
        this.variable = (Entrada.split("\\(")[1]).split("\\)")[0]; // Selecciona lo que esta dentro del parentesis.
    }
    
    public void ShuntingYard(Funcion funcion){ // Se implementa el algoritmo de ShuntingYard de Dijkstra para resolver las ecuaciones.
        int x = 0;
        //System.out.println(variable);
        
        List<String> output = new ArrayList<>();
        List<String> stack = new ArrayList<>();
        
        int index;
        for (index = 0; index < funcion.funcion.length; index++){
            String token = funcion.funcion[index];
            
            if (Character.isLetter(token.charAt(0))){
                if ("x".equals(token)) output.add(variable);
                else stack.add(token);
            } // Si es una funcion va en el Stack
            else if (Character.isDigit(token.charAt(0))) output.add(token); // Si es un numero va al output
            else if ("(".equals(token)) stack.add(token); // Si es un ( va al stack
            else if (")".equals(token)){ // Se envia todo al output y se elimina del stack hasta el (
                while (!"(".equals(stack.get(stack.size()-1))){
                    output.add(stack.get(stack.size()-1)); // Se copia el ultimo elemento del stack en el output
                    stack.remove(stack.size()-1);
                }stack.remove(stack.size()-1); // Se elimina el (
            }
            else if ("+".equals(token) || "-".equals(token) || "*".equals(token) || "/".equals(token)){ // Es un operador. Hay diferentes pasos que seguir
                
                String top;
                if (!stack.isEmpty()){
                    top = stack.get(stack.size()-1);
                    while((Character.isLetter(top.charAt(0)) || 
                    ((("+".equals(token) || "-".equals(token)) && ("+".equals(top) || "-".equals(top) || "*".equals(top) || "/".equals(top)) ||
                     (("*".equals(token) || "/".equals(token)) && ("*".equals(top) || "/".equals(top))))))
                    && (!"(".equals(top)) && !stack.isEmpty()){
                                                                        // Se revisa el elemento que esta al final del stack, y que se cumpla: 
                                                                        //((hay un funcion || tiene mayor o igual precedencia) && (no es parentesis))

                        output.add(stack.get(stack.size()-1));
                        stack.remove(stack.size()-1);
                        if (!stack.isEmpty()) top = stack.get(stack.size()-1);
                    }
                    stack.add(token); // Mientras la condicion se cumpla se mueven los operadores del stack al output, luego se agrega token al stack
                }
                else{
                    stack.add(token);
                }
            } // Se itera hasta que ya no queden tokens
        } // Cuando se acaban los tokens por leer, se mueve todo del stack al output
        while (stack.size() > 0){
            output.add(stack.get(stack.size()-1));
            stack.remove(stack.size()-1);
        }
        // A este punto se tienen las operaciones en Post-Orden
        // Ahora solo hay que resolverlas, lo cual se puede hacer leyendolas de izquierda a derecha.
        
        char elemento;
        int numero1, numero2;
        index = 0;
        
        while (index < output.size()){
            // Cuando se encuentra un operador se debe utilizar con los 2 elementos previos.
            // Una funcion utiliza el elemento que tenga a la izquierda
            elemento = output.get(index).charAt(0); // Guarda el primer char para identificacion.
            
            if (Character.isLetter(elemento)){ // Si es una letra, es una funcion.
                Resolucion nuevaFuncion = new Resolucion(Funciones, output.get(index)+"("+output.get(index-1)+")"); // Thread para resolver la nueva funcion
                Thread t1 = new Thread(nuevaFuncion);
                t1.start();
                
                try{t1.join();}
                catch(Exception ex){}
                
                output.set(index, nuevaFuncion.resultado); // Reemplaza la llamada a funcion por el resultado de esta.
                output.remove(index-1);
                index--;
            }
            else if (!Character.isDigit(elemento) && output.get(index).length() == 1){ // Si el elemento no es un numero
                // La segunda condicion es porque explotaba con los negativos, porque el elemento 1 no era un digito. lel
                numero1 = Integer.parseInt(output.get(index-2));
                numero2 = Integer.parseInt(output.get(index-1));
                        
                switch (output.get(index)) { // Realiza la operacion de los numeros segun corresponda
                    case "+":
                        output.set(index, String.valueOf(numero1+numero2));
                        break;
                    case "-":
                        output.set(index, String.valueOf(numero1-numero2));
                        break;
                    case "*":
                        output.set(index, String.valueOf(numero1*numero2));
                        break;
                    case "/":
                        output.set(index, String.valueOf(numero1/numero2));
                        break;
                }
                output.remove(index-1); // Reemplaza el operador por el resultado y elimina los 2 numeros de la cola.
                output.remove(index-2);
                index-=2;
            }
            index++;
        }
        this.resultado = output.get(index-1);
    }
    
    public int buscarFuncion(char letra){
        int i;
        for (i = 0; i < Funciones.size() ; i++)
            if (Funciones.get(i).letra == letra) return i;
        return 0;
    }
    
    @Override
    public void run(){
        ShuntingYard(Funciones.get(buscarFuncion(funcion))); // Ejecuta ShuntingYard con la funcion que se llamo por consola
    }
}

class Problema1{
    
    public static String[] limpiar(String linea){
        String partes[] = (linea.split("=")[1]).split("");
        List<String> resultado = new ArrayList<>();
        
        int index;
        for (index = 0; index < partes.length; index++){
            String elem = partes[index];
            
            if (Character.isDigit(elem.charAt(0))){ // El caracter leido es un digito
                if (!resultado.isEmpty() && Character.isDigit((resultado.get(resultado.size()-1)).charAt(0))){
                    elem = resultado.get(resultado.size()-1) + elem;
                    resultado.remove(resultado.size()-1);
                    resultado.add(elem);// Se concatenan los digitos para formar el numero
                }
                else resultado.add(elem);
            }
            else resultado.add(elem);
        }
        String array[] = resultado.toArray(new String[resultado.size()]);
        return array;
    }
    
    public static void main(String args[]) throws IOException{
        List<Funcion> Funciones = new ArrayList<>();
        Scanner scan = new Scanner(new BufferedReader(new FileReader("funciones.txt")));
        
        int nFunciones;
        if (scan.hasNextInt())
            nFunciones = scan.nextInt();
        else{ 
            System.out.println("0");
            return;
        }
        scan.nextLine();
        String linea;
        char letra;
        int index;
        
        for (index = 0 ; index < nFunciones ; index++){ // Se leen numeros desde el archivo input.txt
            linea = scan.nextLine();
            letra = linea.charAt(0);
            String parametros[] = limpiar(linea);
            
            Funcion funcion = new Funcion(letra, parametros);
            Funciones.add(funcion);
        }
        System.out.println("Funciones Ingresadas!");
        Scanner input = new Scanner(System.in);
        
        boolean flag = true;
        while(flag){
            System.out.println("Ingrese Operacion:");
            String entrada = input.next();

            Resolucion resultado = new Resolucion(Funciones, entrada);
            Thread t = new Thread(resultado);
            t.start(); // Inicia el Thread con la clase Ordenar

            try{t.join();} // Le hace Join para esperar el resultadon
            catch(Exception ex){}// Le useless catch
            
            System.out.println("\nEl resultado es:");
            System.out.println(resultado.resultado);
        }
    }
}