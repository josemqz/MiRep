import java.io.File;
import java.util.Scanner;
import java.lang.Thread;


//supongo que debe haber un thread por funcion? yes
//hay que iterar revisando funciones hasta llegar a una que no dependa de otras
//se retorna el valor al thread del que dependia esa funcion y asi sucesivamente

class HiLo implements Runnable{

    @Override
    public void run(){

    }

    
    public int func(String lambda) throws Exception{
        //antes de revisar nada, podria buscar las funciones y reemplazarlas
        //con su valor, una vez no hayan funciones, resolver

        //casos base: más que casos base es ir revisando
        //condiciones de recurrencia

        //iterar sobre los primeros 4 caracteres de cada linea para buscar la funcion jsdj
        Scanner fSc = new Scanner(this.arch);
        while (!fSc.next().substring(0,5).equals(lambda)) {
            System.out.print("HiLo!");
        }

        //seccion interpretacion simbolos matematicos

        return 0;
    }



}
//primero se buscan las funciones, resolviendolas de inmediato, luego parentesis luego
//buscar multiplicaciones y divisiones de izq a der para resolver los dos valores
//que estén a sus lados y lo mismo con suma y resta
public class T2{


    public int func(String lambda) throws Exception{
        //antes de revisar nada, podria buscar las funciones y reemplazarlas
        //con su valor, una vez no hayan funciones, resolver

        //casos base: más que casos base es ir revisando
        //condiciones de recurrencia

        //iterar sobre los primeros 4 caracteres de cada linea para buscar la funcion jsdj
        Scanner fSc = new Scanner(this.arch);
        while (!fSc.next().substring(0,5).equals(lambda)) {
            System.out.print("HiLo!");
        }

        //seccion interpretacion simbolos matematicos

        return 0;
    }


    public static void main(String args[]) throws Exception{

        //archivo
        File f = new File("funciones.txt");
        Scanner sc = new Scanner(f);

        //inṕut
        Scanner inp = new Scanner(System.in);
        System.out.print("Ingrese funcion a evaluar: ");
        String fEval = inp.next();
        //pueden pedir cualquier funcion de las n funciones

        int n = sc.nextInt();

        //puedo tener mapeadas las funciones con sus indices correspondientes
        while(sc.hasNext()){

                String L = sc.next();  //idealmente ir a la linea de la funcion requerida
                int i = 5;             //no considera la funcion cuya definicion está siendo leída

                int num_Func = 0; //ver a priori cuantas funciones hay que realizar

                while(i >= 0){
                    i = L.indexOf("(x)",i+1);
                    num_Func++;
                }

                //Arreglo de la cantidad de threads originales a usar
                HiLo Threads[] = new HiLo[num_Func]; //it works <:
                int t;
                for(t = 0; t < num_Func; t++){
                    //crear cada thread en cada posicion del arreglo
                    //ahrn no sé, ah? //Aparentemente en la declaracion del arreglo ya se inicializan todos :oo
                }

                //cada iteracion es una de las funciones encontradas en la funcion principal
                i = 0; t = 0;
                while(i >= 0){

                    i = L.indexOf("(x)",i+1);

                    //Thread / System.out.println(L.replace(L.substring(i-1,i+3),"5"));

                    Threads[t].start();
                    //create(Threads[t], Threads[t].func, L.substring(i-1,i+2));

                    t++;
                }

                //guardar string en variable, si se encuentra una funcion, invocar thread
                //para resolverla y, al retornar el valor, reemplazarlo, y así sucesivamente

        }

        sc.close();

    }
}
