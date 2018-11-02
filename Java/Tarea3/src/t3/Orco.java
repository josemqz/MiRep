package t3;

public class Orco extends Raza {

    private int constitucion;
    private int fuerza;

    public Orco(){
        crearRaza();
    }

    public void crearRaza(){
        setConstitucion(1);
        setFuerza(2);
    }


    public int getFuerza(){
        return getFuerza();
    }

    public int getConstitucion(){
        return getConstitucion();
    }

    public void habilidad(String habil){
        this.habilidad = habil;
    }

    public String getHabilidad(){
        return this.habilidad;
    }
}
