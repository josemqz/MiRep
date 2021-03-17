package t3;

public class Barbaro extends Clase {

    int armadura;
    char estado;

    /*
            Berserker
    Attack type:    Body
    Skill:          Strength
    Armor:          15
    */

    public void crearClase(){
        setArmaduraClass(15);
    }

    public void setArmaduraClass(int armor){
        this.armadura = armor;
    }

    public int getArmaduraClass(){
        return this.armadura;
    }

    public void setEstadoClass(char s){
        this.estado = s;
    }

    public char getEstadoClass(){
        return this.estado;
    }
    public Barbaro(){
        crearClase();
    }


    public void ataque(Personaje j, Personaje e){   //puede atacar el jugador o el enemigo

        int dAt = 0;    //decide si se efectua el ataque
        int dDa = 0;    //daño efectuado
        int DD = 0;     //doble daño

        dAt = Juego.rollDice(20);
        System.out.println("First roll: " + dAt);

    //habilidad: suerte
        if (j.getHabilidad() == "suerte" && dAt == 1){
            while (dAt == 1) {
                dAt = Juego.rollDice(20);
                System.out.println(j.getNombre() + " used luck! He/she gets to roll again");
            }
        }

    //rival en modo de defensa
        if (e.getEstado() == 'd'){
            System.out.println(e.getNombre() + " is on defense mode!");

            int dAt2;
            dAt2 = Juego.rollDice(20);
            System.out.println("Second roll: " + dAt2);

            if (j.getHabilidad() == "suerte" && dAt2 == 1){
                while (dAt2 == 1){
                    dAt2 = Juego.rollDice(20);
                    System.out.println(j.getNombre() + " used luck! He/she gets to roll again");
                }
            }

            if (dAt2 < dAt) dAt = dAt2;
        }
    //valor de dado final
        System.out.println(j.getNombre() +"'s CHOSEN LUCKY NUMBER: " + dAt );

        if (dAt == 20) DD = 1;

        if (dAt >= e.getArmadura() || (j.getHabilidad() == "atacante" && dAt >= 2)){

            if (j.getHabilidad() == "atacante") System.out.println(j.getNombre() + " used his ability as attacker! (refer to manual (ok ok... he/she needed 2+ on his/her dice))");

            dDa = Juego.rollDice(8);
            System.out.println("Damage roll: " + dDa);

            dDa += j.getFuerza();
            System.out.println("Strength bonus! +"+j.getFuerza());

            if (DD == 1){
                dDa *= 2;
                System.out.println("\n\n\t\t*** DOUBLE DAMAGE!!!!! ***\t\t\n\n");
            }
        }

        else{
            if (j.getHabilidad() == "atacante") System.out.println("Attacker! You got less than 2...");
            System.out.println(j.getNombre()+", you missed miserably... (got less than his/her shield)");
        }

    //asignacion de vida
        if (dDa > 0){
            e.asignarVida(e.getVida() - dDa);
            if (e.getVida() > 0){
                System.out.println(e.getNombre() + " HP: " + e.getVida()+"\n\n");
            }
            else{
                e.asignarVida(0);
                System.out.println(e.getNombre() + " IS DEAD!! " + j.getNombre()+ " KILLED HIM/HER!\n\n");
            }
        }
        else{
            System.out.println(j.getNombre() + " didn't hurt " + e.getNombre() + " c:");
            System.out.println(e.getNombre() + " HP: " + e.getVida()+"\n\n");
        }
    }

    public void defender(){
        this.setEstadoClass('d');
    }

}
