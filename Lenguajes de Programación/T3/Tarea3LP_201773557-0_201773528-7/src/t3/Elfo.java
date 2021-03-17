package t3;

public class Elfo extends Raza{

    int fuerza = 0;
    int destreza = 0;
    int constitucion = 0;
    public String habilidad ="";

    public Elfo(){
        this.crearRaza();
    }

    public void crearRaza(){
        this.setDestrezaRace(2);
        this.setConstitucionRace(1);
        this.habilidad("evasion");
    }

    public void setDestrezaRace(int destreza){
        this.destreza = destreza;
    }

    public void setConstitucionRace(int constitucion){
        this.constitucion = constitucion;
    }

    public void setFuerzaRace(int strength){
        this.fuerza = strength;
    }

    public int getDestrezaRace(){
        return this.destreza;
    }
    public int getConstitucionRace(){
        return this.constitucion;
    }

    public int getFuerzaRace(){
        return this.fuerza;
    }
    public void habilidad(String habil){
        this.habilidad = habil;
    }

    public String getHabilidad(){
        return this.habilidad;
    }

}
