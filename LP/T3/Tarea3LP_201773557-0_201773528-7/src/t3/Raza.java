package t3;

public abstract class Raza{

    int fuerza;
    int destreza;
    int constitucion;
    public String habilidad;

    /* Funcion: void crearRaza()
    *   Descripcion: asigna constitucion, destreza, fuerza a la raza, segun corresponda
    *                asigna habilidad de la raza
    *    Return: nada
    *
    */
    public abstract void crearRaza();

    /* Funcion: void habilidad()
    *   Descripcion: setter habilidad
    *    Return: nada
    *
    */
    public abstract void habilidad(String habil);
    public abstract String getHabilidad();

    public abstract void setDestrezaRace(int destreza);
    public abstract void setConstitucionRace(int constitucion);
    public abstract void setFuerzaRace(int strength);
    public abstract int getDestrezaRace();
    public abstract int getConstitucionRace();
    public abstract int getFuerzaRace();

}
