package t3;

public abstract class Clase {
    private int armadura;
    private char estado;
    abstract void crearClase();
    abstract void ataque(Personaje j, Personaje e);
    abstract void defender();


    public void setArmadura(int armor){
        this.armadura = armor;
    }
    public int getArmadura(){
        return this.armadura;
    }

    public void setEstado(char s){
        this.estado = s;
    }
    public char getEstado(){
        return this.estado;
    }
}
