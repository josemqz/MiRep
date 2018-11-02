package t3;

public class Clerigo extends Clase {

    public Clerigo(){
        crearClase();
    }

    public void crearClase(){
        setArmadura(15);
    }

    public void ataque(Personaje j, Personaje e){   //puede atacar el jugador o el enemigo

        int dE = 0;    //decide si se efectua el ataque (enemigo)
        int dDa = 0;    //daño efectuado
        dE = Juego.rollDice(20);

        if (e.getEstado() == 'd'){   //enemigo en modo de defensa
            System.out.println("Enemigo está en modo de defensa!");

            int dE2 = Juego.rollDice(20);

            if (dE2 > dE) dE = dE2;
        }

        if (dE == 20){
            System.out.println("Dado enemigo : 20");
            System.out.println("");
            return;
        }

        dE += e.getConstitucion();  //Clerigo -> Constitucion

        if (dE >= 13){
            dE /= 2;
        }

        dDa = Juego.rollDice(6);

        if (dE >= e.getArmadura()){
            dDa -= dE;
        }

        if (dDa >= 0) e.asignarVida(e.getVida() - dDa);
        else e.asignarVida(0);
    }

    public void defender(){
        setEstado('d');
    }

}
