import java.util.LinkedList;
/*
public class L{

    public static void main(String[] args){
        System.out.println("ah");
        LinkedList<Integer> W = new LinkedList<Integer>();
        W.add(78);
        W.add(10);
        W.add(45);
        java.util.Collections.sort(W);
        for(int i: W){
            System.out.println(i);
        }

        for(int i: W){

            int x = min(W[]);
            W.remove(x);
            W.append(x);

        }




    }

}
*/
class SuperClase {
    int a = 1;
    public SuperClase(){
        a = 3;
    }
    public SuperClase(int a){
        a = this.a;
    }
    void print(){
        System.out.println(a);
    }
}


class SubClase extends SuperClase {
    public int a = 0;
    public SubClase () {
        super(2);
    }
    public SubClase(int b){
        a = b;
    }

    void SubPrint(int a){
        System.out.println(this.a+super.a +a);
    }
}

public class L{
    public static void main(String[] args){
        SubClase s1 = new SubClase();
        SubClase s2 = new SubClase(4);

        s1.print();
        s1.SubPrint(5);
        System.out.println(s1.a);
        s2.print();
        System.out.println(s2.a);
        s2.SubPrint(1);
    }
}
