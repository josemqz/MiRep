package t3;

public interface Personaje {

	void asignarRaza(String R );
	void asignarClase(String C);

	public void asignarVida(int v);
	public void asignarNombre(String Name);
	public void setEstado(char s);

	public int getVida();
	public String getNombre();
	public char getEstado();
	public int getArmadura();

	public String getHabilidad();

	public int getFuerza();
	public int getDestreza();
	public int getConstitucion();
}
