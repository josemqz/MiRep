package t3;
public class Mago extends Clase {

    int armadura;
    char estado;

    /*
            Mage
    Attack type:    Magicaru-Mirakuru-ATTACK
    Skill:          Dexterity
    Armor:          10
    */
    public void crearClase(){
        setArmaduraClass(10);
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

    public Mago(){
        crearClase();    
    }
    
    public void ataque(Personaje j, Personaje e){   //puede atacar el jugador o el enemigo

        int dE = 0;    //decide si se efectua el ataque (enemigo)
        int dDa = 0;    //daño efectuado

        dE = Juego.rollDice(20);
        System.out.println(e.getNombre() + "'s first roll: " + dE);

        //habilidad: suerte
        if (e.getHabilidad() == "suerte" && dE == 1){
            while (dE == 1) {
                dE = Juego.rollDice(20);
                System.out.println(j.getNombre() + " used luck! He/she gets to roll again");
            }
        }

    //rival en modo de defensa
        if (e.getEstado() == 'd'){
            System.out.println(e.getNombre() + " is on defense mode!");

            int dE2 = Juego.rollDice(20);
            if (e.getHabilidad() == "suerte" && dE2 == 1){
                while (dE2 == 1) {
                    dE2 = Juego.rollDice(20);
                    System.out.println(j.getNombre() + " used luck! He/she gets to roll again");
                }
            }

            System.out.println(e.getNombre() + "'s second roll: " + dE2 );

            if (dE2 > dE) dE = dE2;
        }
    //valor de dado final
        System.out.println(e.getNombre() +"'s CHOSEN LUCKY NUMBER: " + dE);

        if (dE == 20 || (e.getHabilidad() == "evasion" && dE >= 2)){
            if (e.getHabilidad() == "evasion") System.out.println(e.getNombre() + " used evasion!");
            System.out.println("\nNothing to do, " + e.getNombre() + " got lucky...\n");
            return;
        }

        dE += e.getDestreza();  //Mago -> Destreza
        System.out.println(e.getNombre() + "'s dexterity bonus +" + e.getDestreza());

        dDa = Juego.rollDice(6);
        System.out.println("Damage roll: " + dDa);

        if (dE >= 13){
            dDa /= 2;
            System.out.println(e.getNombre()+" got over 12!\nDamage reduces to half!\n" + "Final damage: " + dDa);
        }

    //asignacion de vida
        if (dDa > 0){
            e.asignarVida(e.getVida() - dDa);
            if (e.getVida() > 0){
                System.out.println( e.getNombre() + " HP: " + e.getVida()+"\n\n");
            }

            else{
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
