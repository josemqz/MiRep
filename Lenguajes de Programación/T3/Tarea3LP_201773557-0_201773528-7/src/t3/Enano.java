package t3;

public class Enano extends Raza {

    int fuerza = 0;
    int destreza = 0;
    int constitucion = 0;
    public String habilidad ="";

    public Enano(){
        crearRaza();
    }

    public void crearRaza(){
        this.setFuerzaRace(1);
        this.setConstitucionRace(2);
        this.habilidad("resistencia");
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
