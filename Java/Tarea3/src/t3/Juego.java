package t3;


import java.util.Random;
import java.util.Scanner;


public class Juego {

	public static int rollDice(int i){
		Random rand = new Random();
		int num = 0;
		switch (i) {
			case 6:
				num = rand.nextInt(6)+1;
			case 8:
				num = rand.nextInt(8)+1;
			case 20:
				num = rand.nextInt(20)+1;
		}
		return num;
	}


	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Random rq = new Random();
		String c ="";
		String r = "";
		String[] classes = {"Berserker","Cleric","Mage","Rogue"};
		String[] race = {"Human","Orc","Elf","Dwarf"};
		String[] enemies = {"Klrak","Adran","Isaac","Elysium","Krrogh","Jenkins"};
		String Name = "";
		int rand = 0;
		int angeryOmeter = 0;
		int selection = 0;

		Jugador playerOne;

		Enemigo actualEnemy;

		String lastBoss = "";

		int flag = 1;

		try{
			System.out.print("\033[H\033[2J");
			do{

				System.out.println("*go-hom*\nNow tell me...\nAre you a boy or a gi- (0.0)/*****\nnothing...\n*go-hom*\nPlease enter your name Adventurer-san");
				Name = sc.next();

				System.out.println("\nAre you sure you want "+ Name+" as yor name?\nIt CAN´T be changed later...\n(Select 0 or 1)\n\n[0]Yes\n[1]no");

				selection = Integer.parseInt(sc.next());

				System.out.println("Really?");
				selection = Integer.parseInt(sc.next());

				if (selection != 1 || selection !=0){
					int miniFlag = 1;
					System.out.println("Im gonna get maaad");
					do{
						System.out.println("Is "+Name+" right?\nChoose either [0] or [1]\n[0]Yes\n[1]no");
						if (selection == 0 || selection == 1) {
							miniFlag = 0;
						}
					}while(miniFlag !=0);
				}
				if (selection == 0) {
					flag = 0;
				}
			}while(flag != 0);

			System.out.println("Ok Ok... if it's what you really want.... *chuckles*\n");
			flag = 1;

		}catch(Exception e){
			System.out.println("\nAdventurer-san you IDIOT (> O <)/********");
			System.out.println("Your name will be IDIOT-san from now on....\nEnjoy your adventure (> O <)/*****\n");
			Name = "IDIOT-san";
			flag = 1;
			angeryOmeter++;
		}


		try{
			System.out.print("\033[H\033[2J");
			System.out.println("Now... I want you to select your class... please do it well");

			do{
				System.out.println("Class:\n[0]Berserker\t\t[2]Mage\n[1]Cleric       \t[3]Rogue");
				selection = Integer.parseInt(sc.next());
				c = classes[selection];

				System.out.println("Your class is " + classes[selection]+"... Is it correct?\n[0]Yes\n[1]No" );

				selection = Integer.parseInt(sc.next());

				if (selection == 0) {
					flag = 0;

				}

			}while(flag != 0);

		}catch(Exception e){
			System.out.print("\033[H\033[2J");
			System.out.println("\n"+Name+", You Jerk....\nNow your class will be assigned Randomly (heh... stupid)");
			rand = rq.nextInt(3)+1;
			c = classes[rand];
			System.out.println("(That's what you get for doing things I don't like... ( hah))\n\n");
			angeryOmeter++;

		}finally{

			System.out.println("Ok!\nYou are a " + c+" now.\nCongratulations!!!!!!!!!");
			System.out.println("(Oh boi, I feel like Rohan-sensei now....)\n(W8....)\n(*go-hom*.... you didn't hear ANYTHING (>O<)///)\n\n");
		}

		try{
			System.out.println("Aaaaand you know the deal... Choose your race\nDon't even think of screwing this up bigshot... I'll get mad");

			do{
				System.out.println("Race:\n[0]All mighty Human\t\t[2]A beautiful long eared High-Elf\n[1](Dumb) Orc\t\t\t[3]A very smart and crafty Dwarf");
				selection = Integer.parseInt(sc.next());
				System.out.println("Your class is " + race[selection]+"... Is it correct?\n[0]Yes\n[1]No" );
				r = race[selection];

				selection = Integer.parseInt(sc.next());

				if (selection == 0) {
					flag = 0;
				}

			}while(flag != 0);

		}catch(Exception e){
			System.out.print("\033[H\033[2J");
			System.out.println("\n"+Name+", You Jerk....\nNow your race will be assigned Randomly\nThank our graceful king Java-sama for providing the Random() class, ok?");
			rand = rq.nextInt(3)+1;
			r = race[rand];
			System.out.println("(I'm starting to get pissed off, you know)\n\n");
		}finally{
			System.out.println("\nOk!\nYou are a " + r+" now.\nCongratulations!!!!!!!!!");
			System.out.println("Good for you...\nNow let's begin your story "+Name+"!!!!!!!!");
			System.out.println("\n\n\n*Dramatic music starts*\n\n\n");
			System.out.println("*go-hom*");
			System.out.println(Name + " is walking by the city of Order...\nThen... he steps on something");

		}

		/*
								Character creation
		*/
		playerOne = new Jugador(r,c,Name);
		/*
							End of Character Creation
		*/

		try{
			System.out.println("Do you want to say wow?\n[0]Yes, but moderately\n[1]HECK F*CKING YEAH");
			selection = Integer.parseInt(sc.next());

		}catch(Exception e){
			System.out.println("\nB....Baka.....");
			System.out.println("I have an angery-o-meter you know...\nit's based upon your mistakes");
			System.out.println("angery count: "+angeryOmeter+"\nangeryOmeter++;\nOOPS, not supoused to show that lmao");
			System.out.println("----------------------.--------------------");
			angeryOmeter++;



		}finally{
			System.out.println("\n"+Name+":\t- WAO a sacred sword LMAO -\n");
			System.out.println("Do-dododon-do-don! you recieved Lengendary armor[Lv.1] and a legendary sword[Lv.1]");
			System.out.println("From Who? You say...\nFrom me obiously");
			System.out.println("I'm the god of this world\nWell... Kinda");
		}

		System.out.println("\n\nAnyway..."+Name+" is doing whatever the thing it was, aaaand");
		System.out.println("Boooooooom...\n"+Name+" sees someone\n");
		System.out.println("Do you wanna pass RIGHT THROUGH THAT PERSON'S FIELD OF VISION?\n");
		System.out.println("[0]Yes\n[1]ABSOLUTELY YES");

		try{
			selection = Integer.parseInt(sc.next());

		}catch(Exception e){
			System.out.println("\nYou know... the real thing is gonna apperar soon if you don't start taking this HOMEWORK seriously");
			System.out.println("angery count: "+angeryOmeter);
			System.out.println("YEAH BOIII CRANK IT UPPPPPPPPP\n(angery-o-meter++;)");

			System.out.println("----------------------.--------------------");
			angeryOmeter++;
		}

		/*
						Enemy creation
		*/
		actualEnemy = new Enemigo();
		/*
						end of Enemy creation
		*/

		System.out.println("\n"+actualEnemy.getNombre()+": WAGA NA WA MEGUMI-... MY NAME IS "+actualEnemy.getNombre()+" THE FOOLISH, I CHALLENGE YOU TO A DUEL FOR NO REASON WHATSOEVER!!!!!!!!!");

		System.out.println("\n\nOh boi... what do you do now");

		System.out.println("\n[0] NIGERUNDAYOOOOOO (not actually avialable bc it's the law here boi)\t[2] FIGHTING LIKE A MAN");
		System.out.println("[1] Say: 'Please lord save me'                                        \t[3] Become a Super Saiya- ABSOLUTELY NOT");

		try{
			selection = Integer.parseInt(sc.next());
			System.out.println("\nYou selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nI choose you "+Name+"!!!!!!!!!!!\n*beautiful gameGODMasterRace throws player at the enemy*");
		}catch(Exception e){
			System.out.println("\nYou never learn don't you...");
			System.out.println("angery count: "+angeryOmeter);
			System.out.println("angery-o-meter++;");
			System.out.println("\nYou selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nI choose you "+Name+"!!!!!!!!!!!\n*beautiful gameGODMasterRace throws player at the enemy*");
		}






		sc.close();
	}
}
