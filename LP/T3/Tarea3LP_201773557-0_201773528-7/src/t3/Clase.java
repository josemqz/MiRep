package t3;

public abstract class Clase {
    int armadura;
    char estado;

    /* Funcion: void crearClase()
    *   no hay parámetros.
    *   descripción: Configura la armadura de la clase correspondiente
    *   Return: nada
    *
    */
    abstract void crearClase();

    public abstract void setArmaduraClass(int armor);
    public abstract int getArmaduraClass();

    public abstract void setEstadoClass(char s);
    public abstract char getEstadoClass();

    abstract void ataque(Personaje j, Personaje e);
    abstract void defender();
}
