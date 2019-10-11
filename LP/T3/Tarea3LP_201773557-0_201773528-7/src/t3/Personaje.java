package t3;

public interface Personaje {

	/* Funcion: Raza asignarRaza()
	*  	Parametros:
	*		String R: raza seleccionada
	*   Descripcion: asigna la raza correspondiente al personaje
	*    Return: Raza selecconada
	*
	*/
	Raza asignarRaza(String R );

	/* Funcion: Raza asignarclase()
	*	Parametros:
	*		String C: clase seleccionada
	*   Descripcion: asigna la clase correspondiente al personaje
	*    Return: clase selecconada
	*
	*/
	Clase asignarClase(String C);


	/* Funcion: asignarVida()
	*	Parametros:
	*		int v: vida a asignar al personaje
	*   Descripcion: asigna la vida al personaje
	*    Return: nada
	*
	*/
	public void asignarVida(int v);

	/* Funcion: void asignarNombre()
	*  	Parametros:
	*		String Name: Nombre del personaje
	*   Descripcion: asigna el nombre del personaje
	*    Return: Nada
	*
	*/
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


	/* Funcion: void attack()
	*  	Parametros:
	*		Personaje j: Personaje Atacante
	*		Personaje e: Personaje atacado
	*   Descripcion: efectúa la acción de atacar, ya sea de tipo fı́sico o mágico, cambiando
	*	la vida del enemigo en caso de efectuar daño.
	*    Return: nada
	*
	*/
	public void attack(Personaje j, Personaje e);

	/* Funcion: void defend()
	*  	Parametros: nada
	*   Descripcion: se asigna el estado defender
	*    Return: nada
	*
	*/
	public void defend();

	public String getClase();
	public String getRaza();
}
