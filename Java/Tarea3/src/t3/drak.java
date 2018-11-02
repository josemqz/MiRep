import java.util.Scanner;
public class drak{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
		int selection = 0;

        System.out.println("THE EVIL DORAGON HAS APPEARED!!!!!!!\n\n");
        System.out.println("                                FAFNIR");

        System.out.println("HP ===============================================================");

        String Xa = "                                        .  .    `//====-              ____,-'~`\n                                               _   __,----'~~~~~~~~~`-----.__\n";
        String Xc = "                        -.            \\_|// .   /||\\\\  `~~~~`---.___./\n                  ______-==.       _-~o  `\\/    |||  \\\\           _,'`\n";
        String Xe = "            __,--'   ,=='||\\=_    ;_,_,/ _-'|-   |`\\   \\\\        ,'\n        _-'      ,='    | \\\\`.    '',/~7  /-   /  ||   `\\.     /\n";
        String Xg = "       .'       ,'       |  \\\\  \\_  ''  /  /-   /   ||      \\   /\n      / _____  /         |     \\\\.`-_/  /|- _/   ,||       \\ /\n";
        String Xi = "     ,-'     `-|--'~~`--_ \\     `==-/  `| \\'--===-'       _/`\n               '         `-|      /|    )-'\\~'      _,--'''\n";
        String Xk = "                           '-~^\\_/ |    |   `\\_   ,^             /\\\n                                /  \\     \\__   \\/~               `\\__\n";
        String Xm = "                            _,-' _/'\\ ,-'~____-'`-/                 ``===\\\n                           ((->/'    \\|||' `.     `\\.  ,                _||\n";
        String Xo = "             ./                       \\_     `\\      `~---|__i__i__\\--~'_/\n             ./                       \\_     `\\      `~---|__i__i__\\--~'_/\n";
        String Xq = "             `B'\\)                  ///,-'~`__--^-  |-------~~~~^'\n             /^>                           ///,--~`-\\\n            `  `\n";

        System.out.print(Xa+Xc+Xe+Xg+Xi+Xk+Xm+Xo+Xq);
        System.out.println("HP ==================");
        System.out.println("MP ==================");


        System.out.println("\n\n(that's what you get for not listening to me)");
        System.out.println("What do you do?");
        System.out.println("\n[0] NIGERUNDAYOOOOOO (not actually avialable bc it's the law here boi)\t[2] FIGHTING LIKE A MAN");
        System.out.println("[1] Say: 'Please lord save me'                                        \t[3] Become a Super Saiya- ABSOLUTELY NOT");
        try{
			selection = Integer.parseInt(sc.next());
			System.out.println("\nYou selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nI choose you Adventurer-san!!!!!!!!!!!\n*beautiful gameGODMasterRace throws player at the enemy*");
		}catch(Exception e){
			System.out.println("\nYou selected -'ATTACK WITH ALL MY MIGHT'-");
			System.out.println("\nI choose you Adventurer-san!!!!!!!!!!!\n*beautiful gameGODMasterRace throws player at the enemy*");
		}

}
}
