class UnBuenTruco {
	private static int k = 2;

	static private void jugamos ( int u , int [ ] v ) {
	u ++; v [ k ++] += 2;
	}

	public static void main ( String [ ] args ) {
		int [] c = { 0 , 1 , 2 , 3 , 4 , 5 } ;
		jugamos (k , c );
		for (int el: c){
			System.out.println(el);
		}
		System.out.println("k: "+k);
	}
}
