package t3;


import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;


public class Juego {

//colores para los nombres
	public static final String ANSI_RESET = "\u001B[0m";
	public static final String ANSI_RED = "\u001B[31m";
	public static final String ANSI_GREEN = "\u001B[32m";
	public static final String ANSI_YELLOW = "\u001B[33m";

//funcion que hace parpadear un string dado
	public static String Blink(String text){return "\033[5m"+text+"\033[0m";}

//funcion que colorea el nombre de los enemigos
	public static String colorEnemigo(String name) { return ANSI_RED + name + ANSI_RESET; }

	/* Funcion: public static void clearScreen()
	*	No hay parámetros
	*   Descripcion: limpia la pantalla
	*    Return: nada
	*
	*/
	public static void clearScreen() {
	    System.out.print("\033[H\033[2J");
	    System.out.flush();
	}


	/* Funcion: public static int rollDice()
	*  	Parametros:
	*		int i: numero de dado a lanzar
	*   Descripcion: lanza los dados correspondientes
	*    Return: entero con valor obtenido
	*
	*/
	public static int rollDice(int i){
		Random rand = new Random();
		int num = 0;
		switch (i) {
			case 6:
				num = rand.nextInt(6)+1;
				break;
			case 8:
				num = rand.nextInt(8)+1;
				break;
			case 20:
				num = rand.nextInt(20)+1;
				break;
		}
		return num;
	}


	/* Funcion: public static String nameLine()
	*  	Parametros:
	*		String enemyName: nombre del enemigo a asignar un dialogo
	*		int num: numero de linea a seleccionar
	*   Descripcion: asigna una linea de dialogo a un personaje dado
	*   Return: string con dialogo correspondiente
	*
	*/
	public static String nameLine(String enemyName, int num){
		String Line = "";
		switch (num) {

			case 0:
				Line = "MY NAME IS "+enemyName+" THE FOOLISH, I CHALLENGE TO A DUEL FOR NO REASON WHATSOEVER";
				break;
			case 1:
				Line = "Technology is incredible! You can now store and recall items and Pokemon as data via PC!, Also my name is "+enemyName+" Let´s fight!";
				break;
			case 2:
				Line = "This isn´t very cash money of you... I'm "+enemyName+", I'm going to kill you <3";
				break;
			default:
				Line =""+enemyName;
		}
		return Line;
	}


	/* Funcion: public static ArrayList<Enemigo> generateEnemiesList()
	*   Descripcion: crea una lista de enemigos, generada aleatoriamente
	*   Return: una lista con los enemigos
	*
	*/
	public static ArrayList<Enemigo> generateEnemiesList(){
		ArrayList<Enemigo> Enemies = new ArrayList<Enemigo>();
		int i;
		Enemigo Enemigo;
		for (i = 0; i < 5; i++) {
			Enemigo = new Enemigo();
			Enemies.add(Enemigo);
		}
		return Enemies;
	}


	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Random rq = new Random();

		Jugador playerOne;
		String Name = "";
		String iName = "";
		String c = "";
		String r = "";

		String[] classes = {"Berserker","Cleric","Mage","Rogue"};
		String[] race = {"Human","Orc","Elf","Dwarf"};
		String[] enemies = {"Klrak","Adran","Isaac","Elysium","Krrogh","Jenkins"};

		ArrayList<Enemigo> Enemies = generateEnemiesList();
		int EnemiesDefeated = 0;
		int ELine = 0;
		int randEnemyState;

		int rand = 0;
		int angeryOmeter = 0;
		int selection = 0;

        String anyKey;

		int flag = 1;

	//Selección de nombre
		try{
			System.out.println("\nBeautifulGameGODMasterRace: Now tell me...\nBeautifulGameGODMasterRace: Are you a boy or a gi- (0.0)/*****\nBeautifulGameGODMasterRace: nothing...\nBeautifulGameGODMasterRace: Puh-lease enter your name Adventurer");
			do{
				System.out.println("Adventurer's name:");

				iName = sc.next();
				Name = ANSI_YELLOW + iName + ANSI_RESET;

				System.out.println("BeautifulGameGODMasterRace: Are you sure you want "+ Name+" as yor name?\nIt CAN´T be changed later...\n(Select 0 or 1)\n\n[0]Yes\n[1]no");

				selection = Integer.parseInt(sc.next());

				if (selection == 0) {
					System.out.println("\nReally?\n(Select 0 or 1)\n\n[0]Yes\n[1]no");
					selection = Integer.parseInt(sc.next());
 				}

				if (selection != 1 && selection !=0){
					int miniFlag = 1;
					System.out.println("BeautifulGameGODMasterRace: Im gonna get maaad");
					do{
						System.out.println("BeautifulGameGODMasterRace: Is "+ Name +" right?\nBeautifulGameGODMasterRace: Choose either [0] or [1]\n[0]Yes\n[1]no");
						selection = Integer.parseInt(sc.next());
						clearScreen();
                        if (selection == 0 || selection == 1) {
							miniFlag = 0;
						}
					}while(miniFlag !=0);
				}
				if (selection == 0) {
					flag = 0;
				}
				clearScreen();

			}while(flag != 0);

			System.out.println("BeautifulGameGODMasterRace: Ok Ok... if it's what you really want....\n");
			flag = 1;

		}catch(Exception e){
            clearScreen();
			System.out.println("\nAdventurer pls stap (> O <)/********");
			System.out.println("BeautifulGameGODMasterRace: Your name will be "+ ANSI_YELLOW +"JohnTitor" + ANSI_RESET +"\nBeautifulGameGODMasterRace: from now on....\nBeautifulGameGODMasterRace: Enjoy your adventure (> O <)/*****\n");
			Name = ANSI_YELLOW +"JohnTitor" + ANSI_RESET ;
			flag = 1;
			angeryOmeter++;
		}

	//Selección de clase
		try{
			System.out.println("BeautifulGameGODMasterRace: Now... I want you to select your " + Blink("CLASS") + "... please do it well");
			do{
				System.out.println("Class:\n[0]Berserker\t\t[2]Mage\n[1]Cleric       \t[3]Rogue");
				selection = Integer.parseInt(sc.next());
				c = classes[selection];

				System.out.println("BeautifulGameGODMasterRace: Your class is " + classes[selection]+"... Is it correct?\n[0]Yes\n[1]No" );

				selection = Integer.parseInt(sc.next());

				if (selection == 0) {
					flag = 0;
				}
            clearScreen();

			}while(flag != 0);

		}catch(Exception e){
			clearScreen();
			System.out.println("\nBeautifulGameGODMasterRace: "+ Name +", BOI pls do it correctly from now on....\nBeautifulGameGODMasterRace: Now your class will be assigned Randomly (heh... stupid)");
			rand = rq.nextInt(3)+1;
			c = classes[rand];
			System.out.println("(BeautifulGameGODMasterRace: That's what you get for doing things I don't like... ( hah))\n\n");
			angeryOmeter++;

		}finally{

			System.out.println("BeautifulGameGODMasterRace: Ok!\nBeautifulGameGODMasterRace: You are a " + c+" now.\nBeautifulGameGODMasterRace: Congratulations!!!!!!!!!\n");
			flag = 1;
		}

	//Selección de raza
		try{
			System.out.println("BeautifulGameGODMasterRace: Aaaaand you know the deal... Choose your " + Blink("RACE"));
			System.out.println("BeautifulGameGODMasterRace: Don't even think of screwing this up bigshot... I'll get mad");

			do{
				System.out.println("Race:\n[0]All mighty Human\t\t[2]A beautiful long eared High-Elf\n[1](Dumb) Orc\t\t\t[3]A very smart and crafty Dwarf");
				selection = Integer.parseInt(sc.next());
				System.out.println("BeautifulGameGODMasterRace: Your class is " + race[selection]+"... Is it correct?\n[0]Yes\n[1]No" );
				r = race[selection];

				selection = Integer.parseInt(sc.next());

				if (selection == 0) {
					flag = 0;
				}
				clearScreen();

			}while(flag != 0);

		}catch(Exception e){
			clearScreen();
			System.out.println("\nBeautifulGameGODMasterRace: "+ Name+", You Jerk....\nBeautifulGameGODMasterRace: Now your race will be assigned Randomly\nBeautifulGameGODMasterRace: Thank our graceful king Java-sama for providing the Random() class, ok?");
			rand = rq.nextInt(3)+1;
			r = race[rand];
			System.out.println("BeautifulGameGODMasterRace: I'm starting to get pissed off, you know\n\n");
		}finally{

			System.out.println("\nBeautifulGameGODMasterRace: Ok!\nBeautifulGameGODMasterRace: You are a " + r+" now.\nBeautifulGameGODMasterRace: Congratulations!!!!!!!!!");
			System.out.println("BeautifulGameGODMasterRace: Good for you...\nBeautifulGameGODMasterRace: Now let's begin your story "+ Name+ "!!!!!!!!");
			System.out.println("\n\n\n*Dramatic music starts*\n\n\n");
			System.out.println("BeautifulGameGODMasterRace: "+ Name + " is walking by the city of Order...\n");
			System.out.println("BeautifulGameGODMasterRace: Then... he steps on something");

		}

		/*
								Character creation
		*/
		playerOne = new Jugador(r,c,Name);
		/*
							End of Character Creation
		*/

//wow line
		try{
			System.out.println("BeautifulGameGODMasterRace: Do you want to say wow?\n[0]Yes, but moderately\n[1]HECK F*ING YEAH");
			selection = Integer.parseInt(sc.next());
			clearScreen();

			if (selection != 1 && selection !=0){
				int miniFlag = 1;
				System.out.println("BeautifulGameGODMasterRace: Are you going to keep messing with me? I swear if you go on...\n");
				do{
					System.out.println("BeautifulGameGODMasterRace: Do you want to say wow?\n[0]Yes, but moderately\n[1]HECK F*CKING YEAH");
					selection = Integer.parseInt(sc.next());
					if (selection == 0 || selection == 1) {
						miniFlag = 0;
					}
				}while(miniFlag !=0);
			}

		} catch(Exception e){
			clearScreen();
			System.out.println("BeautifulGameGODMasterRace: I have an angery-o-meter you know...\nBeautifulGameGODMasterRace: it's based upon your mistakes");
			System.out.println("angery count: "+angeryOmeter+"\nangeryOmeter++;\nBeautifulGameGODMasterRace: OOPS, not supoused to show that lmao");
			System.out.println("----------------------.--------------------");
			angeryOmeter++;


		}finally{
			System.out.println("\n"+Name+":\t- WAO a sacred sword LMAO -\n");
			System.out.println("BeautifulGameGODMasterRace: Do-dododon-do-don! you recieved Lengendary armor[Lv.1] and a legendary sword[Lv.1]");
			System.out.println("BeautifulGameGODMasterRace: From Who? You say...\nBeautifulGameGODMasterRace: From me obviously");
			System.out.println("BeautifulGameGODMasterRace: I'm the god of this world\nBeautifulGameGODMasterRace: Well... Kinda");
		}

		System.out.println("\n\nBeautifulGameGODMasterRace: Anyway..."+ Name+" is doing whatever the thing it was, aaaand");
		System.out.println("BeautifulGameGODMasterRace: Boooooooom...\nBeautifulGameGODMasterRace: "+Name+ " sees someone\n");
		System.out.println("BeautifulGameGODMasterRace: Do you wanna pass RIGHT THROUGH THAT PERSON'S FIELD OF VISION?\n");
		System.out.println("[0]Yes\n[1]ABSOLUTELY YES");

	//Avistamiento de enemigo
		try{
			selection = Integer.parseInt(sc.next());
			clearScreen();
			if (selection != 1 && selection !=0){
				int miniFlag = 1;
				System.out.println("BeautifulGameGODMasterRace: YOU HAVE GOT TO BE F*CKING WITH ME! (Ò.Ó)");
				angeryOmeter++;
				do{
					System.out.println("BeautifulGameGODMasterRace: Do you wanna pass RIGHT THROUGH THAT PERSON'S FIELD OF VISION?\n[0]Yes\n[1]ABSOLUTELY YES");
					selection = Integer.parseInt(sc.next());
					if (selection == 0 || selection == 1) {
						miniFlag = 0;
					}
				}while(miniFlag !=0);
			}

		}catch(Exception e){
			clearScreen();
			System.out.println("\nBeautifulGameGODMasterRace: You know... the real thing is gonna appear soon if you don't start taking this HOMEWORK seriously");
			System.out.println("angery count: "+angeryOmeter);
			System.out.println("BeautifulGameGODMasterRace: YEAH BOIII CRANK IT UPPPPPPPPP\n(angery-o-meter++;)");

			System.out.println("----------------------.--------------------");
			angeryOmeter++;
		}

		int turn = 0;
		rand = 0;


	//Batallas con los rivales de la lista
		try{
			while(EnemiesDefeated < 3 && playerOne.getVida() > 0){

				turn = 1;

				System.out.println("\n\n\n"+colorEnemigo(Enemies.get(rand).getNombre().toUpperCase())+": "+nameLine(colorEnemigo(Enemies.get(rand).getNombre().toUpperCase()), ELine)+"\n");

		//Stats

            //Enemigo
				System.out.println("\033[1m\033[4m" + colorEnemigo(Enemies.get(rand).getNombre()) + "\033[0m");
				System.out.println(" Race: " + Enemies.get(rand).getRaza() + "\t" + "Class: " + Enemies.get(rand).getClase());
				System.out.println(" Hability: " + Enemies.get(rand).getHabilidad());
				System.out.print(" Strength: " + Enemies.get(rand).getFuerza() + "  |  ");
				System.out.print("Constitution: " + Enemies.get(rand).getConstitucion() + "  |  ");
				System.out.println("Dexterity: " + Enemies.get(rand).getDestreza());
				System.out.println(" Armor: " + Enemies.get(rand).getArmadura());
				System.out.println(" HP: " + Enemies.get(rand).getVida() + "\n\n");

            //Jugador
				System.out.println("\033[1m\033[4m" + playerOne.getNombre() + "\033[0m");
				System.out.println(" Race: " + playerOne.getRaza() + "\t" + "Class: " + playerOne.getClase());
				System.out.println(" Hability: " + playerOne.getHabilidad());
				System.out.print(" Strength: " + playerOne.getFuerza() + "  |  ");
				System.out.print("Constitution: " + playerOne.getConstitucion() + "  |  ");
				System.out.println("Dexterity: " + playerOne.getDestreza());
				System.out.println(" Armor: " + playerOne.getArmadura());
				System.out.println(" HP: " + playerOne.getVida());

				System.out.println("\n\nbeautifulGameGODMasterRace: Oh boi... what do you do now.....\n\n");

			//estado: ataque
				playerOne.setEstado('a');
				Enemies.get(rand).setEstado('a');
				do{
					System.out.println("\033[1mTurn " + turn + "\033[0m");

				//habilidad: resistencia
					if (playerOne.getHabilidad() == "resistencia") {
						playerOne.asignarVida(playerOne.getVida() + 1);
						System.out.println(playerOne.getNombre() + " has resistance! HP +1");
					}
					if (Enemies.get(rand).getHabilidad() == "resistencia"){
						Enemies.get(rand).asignarVida(Enemies.get(rand).getVida() + 1);
						System.out.println(Enemies.get(rand).getNombre() + " has resistance! HP +1");
					}


					System.out.println("beautifulGameGODMasterRace: C'mon do your thing");
					System.out.println("\n[0] NIGERUNDAYOOOOOO (not actually available bc it's the law here boi)\t[2] FIGHTING LIKE A MAN");
					System.out.println("[1] Say: 'Please lord save me' (defend)                               \t[3] Become a Super Saiya- ABSOLUTELY NOT");

					selection = Integer.parseInt(sc.next());
                    System.out.println();

					if (selection == 2  || selection == 0 || selection == 3){
						if (selection == 0 || selection == 3) {
							System.out.println("beautifulGameGODMasterRace: You know that options [0] and [3] aren't actually available right?");
							System.out.println("beautifulGameGODMasterRace: They're just for the drama LOL");
							System.out.println("beautifulGameGODMasterRace: Anyway, you'll be atacking now, GET READY!");
						}
						System.out.println("You selected -'ATTACK WITH ALL MY MIGHT'-");
						System.out.println("beautifulGameGODMasterRace: I choose you "+playerOne.getNombre()+"!!!!!!!!!!!");
						System.out.println("*beautifulGameGODMasterRace throws player at the enemy*\n");

						System.out.println("IT'S " + playerOne.getNombre() + "'s TURN!");

						playerOne.setEstado('a');
						playerOne.attack(playerOne, Enemies.get(rand));
					}


					else if (selection == 1){
						playerOne.defend();
					}

					//cheat for final DORAGON!!!!!!!! (ends game)
					else if(selection == 98367828){
						playerOne.asignarVida(0);
						Enemies.get(rand).asignarVida(0);
						angeryOmeter = 5;
						break;
					}

					if (Enemies.get(rand).getVida() <= 0){
						if (EnemiesDefeated == 0){

							System.out.println("\n\n\nbeautifulGameGODMasterRace: YOU ARE OFICIALLY AN AWFUL MONSTER. SHAME ON YOU");
							System.out.println("beautifulGameGODMasterRace: ... I mean, well done! You just won your first battle!\n"+Blink("[XP + 17000]"));
							System.out.println(Blink("[LEVEL UP!]\n\n"));
							System.out.println("beautifulGameGODMasterRace: Anyway... The story contiues, blah blah blah");
							System.out.println("beautifulGameGODMasterRace: Oh look, another rival, let's say hi (you have no other options LOL)\n\n");
                            
                            System.out.println("Write anything to continue... (not space pls)");
        					anyKey = sc.next();
                            clearScreen();
							break;
						}
						else if (EnemiesDefeated > 0 && EnemiesDefeated < 2){

							System.out.println("\n\n\nbeautifulGameGODMasterRace: You are getting used to killing people aren't you?... SHAME ON YOU...");
							System.out.println("beautifulGameGODMasterRace: I mean, well done!\nbeautifulGameGODMasterRace: Here, have this\n"+Blink("[XP + 17000]"));
							System.out.println(Blink("[LEVEL UP!]\n\n"));
							System.out.println("beautifulGameGODMasterRace: Anyway... The story contiues, blah blah blah");
							System.out.println("beautifulGameGODMasterRace: Oh look, another rival, let's say hi (you have no other options LOL)\n\n");
                            
                            System.out.println("Write anything to continue... (not space pls)");
							anyKey = sc.next();
                            clearScreen();
                            break;
						}
						else{
							System.out.println("\n\n\n*****************************************");
							System.out.println("*           THANK YOU MARIO             *");
							System.out.println("* BUT OUR PRINCESS IS IN ANOTHER CASTLE *");
							System.out.println("*****************************************");
							System.out.println("\nbeautifulGameGODMasterRace: THE GAME");
                            System.out.println("\nHope you enjoyed ^ ^");
							break;
						}
					}

				//eleccion aleatoria de estado enemigo
					randEnemyState = rq.nextInt(2) + 1;

					System.out.println("IT'S " + colorEnemigo(Enemies.get(rand).getNombre()) + "'s TURN!");
					if (randEnemyState == 1){
						Enemies.get(rand).setEstado('a');
						Enemies.get(rand).attack(Enemies.get(rand), playerOne);
					}
					else{
						Enemies.get(rand).setEstado('d');
						System.out.println(colorEnemigo(Enemies.get(rand).getNombre()) + " is defending\n");
					}

					if (playerOne.getVida() <= 0){
						System.out.println(playerOne.getNombre()+" YOU ARE DEAD!\nbeautifulGameGODMasterRace: HAHA LOL LMAO GIT GUD!\n");
					}
					turn++;
				} while(playerOne.getVida() > 0 && Enemies.get(rand).getVida() > 0);

				rand++;

				if(playerOne.getVida() > 0) {
					EnemiesDefeated++;
					ELine++;
				}
			}


		}catch(Exception e){
			clearScreen();
			System.out.println("\nBeautifulGameGODMasterRace: You never learn don't you...");
			System.out.println("angery count: "+angeryOmeter);
			System.out.println("angery-o-meter++;");
		}

		if (playerOne.getVida() == 0){
			if (angeryOmeter>=2) LassBossXheroFunc(Name);
		}

		sc.close();


	}



	/* Funcion: public static void LassBossXheroFunc()
	*  	Parametros:
	*		String Name: nombre del heroico personaje a enfrenterse al mitico DORAGON Fafnir
	*   Descripcion: muestra una serie de strings por pantalla
	*    Return: nada
	*
	*/
	public static void  LassBossXheroFunc(String Name){
		Scanner sc = new Scanner(System.in);
		int selection = 0;
		clearScreen();

		System.out.println("BeautifulGameGODMasterRace: THE EVIL DORAGON FAFNIR HAS APPEARED!!!!!!!\n\n");
		System.out.println("                                FAFNIR");

		System.out.println("HP ===============================================================");

		String Xa = "                                        .  .    `//====-              ____,-'~`\n                                               _   __,----'~~~~~~~~~`-----.__                        -.            \\_|// .   /||\\\\  `~~~~`---.___./\n                  ______-==.       _-~o  `\\/    |||  \\\\           _,'`\n";
		String Xe = "            __,--'   ,=='||\\=_    ;_,_,/ _-'|-   |`\\   \\\\        ,'\n        _-'      ,='    | \\\\`.    '',/~7  /-   /  ||   `\\.     /       .'       ,'       |  \\\\  \\_  ''  /  /-   /   ||      \\   /\n      / _____  /         |     \\\\.`-_/  /|- _/   ,||       \\ /\n";
		String Xi = "     ,-'     `-|--'~~`--_ \\     `==-/  `| \\'--===-'       _/`\n               '         `-|      /|    )-'\\~'      _,--'''                           '-~^\\_/ |    |   `\\_   ,^             /\\\n                                /  \\     \\__   \\/~               `\\__\n";
		String Xm = "                            _,-' _/'\\ ,-'~____-'`-/                 ``===\\\n                           ((->/'    \\|||' `.     `\\.  ,                _||             ./                       \\_     `\\      `~---|__i__i__\\--~'_/\n             ./                       \\_     `\\      `~---|__i__i__\\--~'_/\n";
		String Xq = "             `B'\\)                  ///,-'~`__--^-  |-------~~~~^'\n             /^>                           ///,--~`-\\\n            `  `\n";

		System.out.print(Xa+Xe+Xi+Xm+Xq);
		System.out.println(Name);
		System.out.println("HP ==================");
		System.out.println("MP ==================");


		System.out.println("\n\n(BeautifulGameGODMasterRace: that's what you get for not listening to me)");
		System.out.println("BeautifulGameGODMasterRace: What do you do?");
		System.out.println("\n[0] NIGERUNDAYOOOOOO (not actually available bc it's the law here boi)\t[2] FIGHTING LIKE A MAN");
		System.out.println("[1] Say: 'Please lord save me'                                        \t[3] Become a Super Saiya- ABSOLUTELY NOT");
		try{
			selection = Integer.parseInt(sc.next());
			System.out.println("\nBeautifulGameGODMasterRace: You selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nBeautifulGameGODMasterRace: I choose you " + Name + "!!!!!!!!!!!\n*BeautifulGameGODMasterRace throws player at the enemy*");
		}catch(Exception e){
			System.out.println("\nBeautifulGameGODMasterRace: You selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nBeautifulGameGODMasterRace: I choose you " + Name + "!!!!!!!!!!!\n*BeautifulGameGODMasterRace throws player at the enemy*");
		}finally{
			clearScreen();
			System.out.println("\n<------------To Be Continued");
			System.out.println("\nBeautifulGameGODMasterRace: Pfffff, lol I'm not gonna do such a tiring work as doing an entire game lol");
			System.out.println("\nBeautifulGameGODMasterRace: KTHXBYE");
			sc.close();
		}
	}
}
