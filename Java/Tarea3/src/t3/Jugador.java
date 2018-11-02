package t3;

import java.util.Random;

public class Jugador implements Personaje {
	Humano Razz1;
	Elfo Razz2;
	Orco Razz3;
	Enano Razz4;
	Enano Razz0;

	Barbaro Klass1;
	Clerigo Klass2;
	Mago Klass3;
	Picaro Klass4;
	Mago Klass0;

	int ic;
	int ir;

	Random r = new Random();

	String[] classes = {"Berserker","Cleric","Mage","Rogue"};
	String[] race = {"Human","Orc","Elf","Dwarf"};

	private int vida;
	private String nombre;

	public Jugador(String R, String C, String Name){
		asignarRaza(R);
		System.out.printf("Const: %d\n", this.Razz2.getDestreza());
		asignarVidaInit();
		asignarClase(C);
		asignarNombre(Name);
	}


	public void asignarClase(String C) {

		switch(C){
			case "Berserker":
			Klass1 = new Barbaro();
			this.ic = 1;
			break;

			case "Cleric":
			Klass2 = new Clerigo();
			this.ic = 2;
			break;

			case "Mage":
			Klass3 = new Mago();
			this.ic = 3;
			break;

			case "Rogue":
			Klass4 = new Picaro();
			this.ic = 4;
			break;

			default:
			Klass0 = new Mago();
			this.ic = 0;
			break;
		}
	}

	public void asignarRaza(String R) {

		switch(R){
			case "Human":
			Razz1 = new Humano();
			this.ir = 1;
			break;

			case "Elf":
			Razz2 = new Elfo();
			this.ir = 2;
			break;

			case "Orc":
			Razz3 = new Orco();
			this.ir = 3;
			break;

			case "Dwarf":
			Razz4 = new Enano();
			this.ir = 4;
			break;

			default:
			Razz0 = new Enano();
			this.ir = 0;
			break;
		}
	}

	public void asignarVida(int v){
		this.vida = v;
	}


	public void asignarVidaInit(){
		switch(this.ir){
			case 1:
				this.vida = Razz1.getConstitucion()+10;
				break;

			case 2:
				this.vida = Razz2.getConstitucion()+10;
				break;

			case 3:
				this.vida = Razz3.getConstitucion()+10;
				break;

			case 4:
				this.vida = Razz4.getConstitucion()+10;
				break;

			case 0:
				this.vida = Razz0.getConstitucion()+10;
				break;
		}
	}

	public int getVida(){
		return this.vida;
	}

	public void asignarNombre(String Name) {
		this.nombre = Name;

	}

	public String getNombre(){
		return this.nombre;
	}

	public void setArmadura(int armor){
		switch(this.ic){
			case 1:
				Klass1.setArmadura(armor);
			break;

			case 2:
				Klass2.setArmadura(armor);
			break;

			case 3:
				Klass3.setArmadura(armor);
			break;

			case 4:
				Klass4.setArmadura(armor);
			break;

			case 0:
				Klass0.setArmadura(armor);
			break;
		}
	}
	public int getArmadura(){
		switch(this.ic){
			case 1:
				return Klass1.getArmadura();

			case 2:
				return Klass2.getArmadura();

			case 3:
				return Klass3.getArmadura();

			case 4:
				return Klass4.getArmadura();

			default:
				return Klass0.getArmadura();
		}
	}

	public void setEstado(char s){
		switch(this.ic){
			case 1:
				Klass1.setEstado(s);
				break;

			case 2:
				Klass2.setEstado(s);
				break;

			case 3:
				Klass3.setEstado(s);
				break;

			case 4:
				Klass4.setEstado(s);
				break;

			case 0:
				Klass0.setEstado(s);
				break;
		}
	}

	public char getEstado(){
		switch(this.ic){
			case 1:
				return Klass1.getEstado();

			case 2:
				return Klass2.getEstado();

			case 3:
				return Klass3.getEstado();

			case 4:
				return Klass4.getEstado();

			default:
				return Klass0.getEstado();
		}
	}

	public int getFuerza(){
		switch(this.ir){
			case 1:
				return Razz1.getFuerza();

			case 2:
				return Razz2.getFuerza();

			case 3:
				return Razz3.getFuerza();

			case 4:
				return Razz4.getFuerza();

			default:
				return Razz0.getFuerza();
		}
	}

	public int getConstitucion(){
		switch(this.ir){
			case 1:
				return Razz1.getConstitucion();

			case 2:
				return Razz2.getConstitucion();

			case 3:
				return Razz3.getConstitucion();

			case 4:
				return Razz4.getConstitucion();

			default:
				return Razz0.getConstitucion();
		}
	}

	public int getDestreza(){
		switch(this.ir){
			case 1:
				return Razz1.getDestreza();

			case 2:
				return Razz2.getDestreza();

			case 3:
				return Razz3.getDestreza();

			case 4:
				return Razz4.getDestreza();

			default:
				return Razz0.getDestreza();
		}
	}

	public String getHabilidad(){
		switch(this.ir){
			case 1:
				return Razz1.getHabilidad();

			case 2:
				return Razz2.getHabilidad();

			case 3:
				return Razz3.getHabilidad();

			case 4:
				return Razz4.getHabilidad();

			default:
				return Razz0.getHabilidad();
		}
	}

}
