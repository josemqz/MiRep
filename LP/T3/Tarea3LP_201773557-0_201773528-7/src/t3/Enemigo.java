package t3;

import java.util.Random;

public class Enemigo implements Personaje {
	Raza Razz;
	Clase Klass;
	private String nombre;
	private String estado;

	private int vida;
	String Clase;
	String Raza;


	String[] enemies = {"Klrak","Adran","Isaac","Elysium","Krrogh","Jenkins"};
	Random r = new Random();

	String[] classes = {"Berserker","Cleric","Mage","Rogue"};
	String[] race = {"Human","Orc","Elf","Dwarf"};


	public Enemigo(){
		asignarNombre("");
		asignarVidaInit();
	}


	public void asignarNombre(String Name) {
		this.nombre = enemies[r.nextInt(5)+1];

		if (this.nombre == "Klrak" ){
			Klass = asignarClase("Berserker");
			Razz = asignarRaza("Dwarf");
		}
		else if (this.nombre == "Adran" ){
			Klass = asignarClase("Rogue");
			Razz = asignarRaza("Elf");
		}
		else if (this.nombre == "Isaac" ){
			Klass = asignarClase("Cleric");
			Razz = asignarRaza("Human");
		}
		else if (this.nombre == "Elysium" ){
			Klass = asignarClase("Mage");
			Razz = asignarRaza("Elf");
		}

		else if (this.nombre == "Krrogh" ){
			Klass = asignarClase("Berserker");
			Razz = asignarRaza("Orc");
		}
		else{
			Klass = asignarClase("Mage");
			Razz = asignarRaza("Human");
		}
	}

	public Clase asignarClase(String C) {
		this.Clase = C;
		switch(C){
			case "Berserker":
			Barbaro Klass1 = new Barbaro();
			return (Clase)Klass1;

			case "Cleric":
			Clerigo Klass2 = new Clerigo();
			return (Clase)Klass2;

			case "Mage":
			Mago Klass3 = new Mago();
			return (Clase)Klass3;

			case "Rogue":
			Picaro Klass4 = new Picaro();
			return (Clase)Klass4;

			default:
			Mago Klass0 = new Mago();
			return (Clase)Klass0;
		}
	}

	public Raza asignarRaza(String R) {
		this.Raza = R;
		switch(R){
			case "Human":
			Humano Razz1 = new Humano();
			return (Raza)Razz1;

			case "Elf":
			Elfo Razz2 = new Elfo();
			return (Raza)Razz2;

			case "Orc":
			Orco Razz3 = new Orco();
			return (Raza)Razz3;

			case "Dwarf":
			Enano Razz4 = new Enano();
			return (Raza)Razz4;

			default:
			Enano Razz0 = new Enano();
			return (Raza)Razz0;
		}
	}

	public void asignarVida(int v){
		this.vida = v;
	}


	public void asignarVidaInit() {
		this.vida = Razz.getConstitucionRace()+8;
	}

	public int getVida(){
		return this.vida;
	}


	public String getNombre(){
		return this.nombre;
	}


	public void setArmadura(int armor){
		Klass.setArmaduraClass(armor);
	}
	public int getArmadura(){
		return Klass.getArmaduraClass();
	}

	public void setEstado(char s){
		Klass.setEstadoClass(s);
	}
	public char getEstado(){
		return Klass.getEstadoClass();
	}

	public int getFuerza(){
		return Razz.getFuerzaRace();
	}
	public int getConstitucion(){
		return Razz.getConstitucionRace();
	}
	public int getDestreza(){
		return Razz.getDestrezaRace();
	}

	public String getHabilidad(){
		return Razz.getHabilidad();
	}

	public void attack(Personaje j, Personaje e){
		Klass.ataque(j, e);
	}
	public void defend(){
		Klass.defender();
	}

	public String getClase(){
		return this.Clase;
	}
	public String getRaza(){
		return this.Raza;
	}
}
