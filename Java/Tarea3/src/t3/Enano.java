package t3;

public class Enano extends Raza {
    private int constitucion;
    private int fuerza;

    public Enano(){
        crearRaza();
    }

    public void crearRaza(){
        setFuerza(1);
        setConstitucion(2);
    }

    public int getConstitucion(){
        return getConstitucion();
    }

    public int getFuerza(){
        return getFuerza();
    }
    public void habilidad(String habil){
        this.habilidad = habil;
    }

    public String getHabilidad(){
        return this.habilidad;
    }

}
