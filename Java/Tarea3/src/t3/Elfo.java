package t3;

public class Elfo extends Raza{

    public Elfo(){
        crearRaza();
    }

    public void crearRaza(){
        setDestreza(2);
        setConstitucion(1);
    }

    public void habilidad(String habil){
        this.habilidad = habil;
    }

    public String getHabilidad(){
        return this.habilidad;
    }

}
