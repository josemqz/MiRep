package t3;

public abstract class Raza{

    private int fuerza = 0;
    private int destreza = 0;
    private int constitucion = 0;
    public String habilidad ="";

    public abstract void crearRaza();
    public abstract void habilidad(String habil);
    public abstract String getHabilidad();

    public void setDestreza(int destreza){
        this.destreza = destreza;
    }

    public void setConstitucion(int constitucion){
        this.constitucion = constitucion;
    }

    public void setFuerza(int strenght){
        this.fuerza = strenght;
    }

    public int getDestreza(){
        return this.destreza;
    }
    public int getConstitucion(){
        return this.constitucion;
    }

    public int getFuerza(){
        return this.fuerza;
    }

}
