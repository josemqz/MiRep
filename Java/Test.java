import java.util.Scanner;

public class Test{
    public static String num(int x){
        char[] A = {'a','b','c','d'};
        int i,j = 0;
        String B = "";
        while (j++ < x){
            for (i = 0; i < 4; i++){
                B += A[i];
            }
        }

        return B;
    }

    public static void main(String[] args){

        System.out.print("iteraciones: ");

        Scanner j = new Scanner(System.in);
        int m = j.nextInt();
        j.close();
        if (m < 10){
            System.out.println("algo: ");
            System.out.println(j);
        }

        System.out.println(num(m));
    }
}
