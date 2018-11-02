package t3;

public class Humano extends Raza {

    private int fuerza;
    private int constitucion;
    private int destreza;

    public Humano(){
        crearRaza();
    }

    public void crearRaza(){
        setFuerza(1);
        setConstitucion(1);
        setDestreza(1);
    }


    public int getFuerza(){
        return getFuerza();
    }


    public int getConstitucion(){
        return getConstitucion();
    }

    public int getDestreza(){
        return getDestreza();
    }
    public void habilidad(String habil){
        this.habilidad = habil;
    }

    public String getHabilidad(){
        return this.habilidad;
    }

}
