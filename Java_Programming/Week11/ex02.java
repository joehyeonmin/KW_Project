package hw11;

public class ex02 {
	public static void main(String[] args) {
		PairGen<String, Integer> p1 = new PairGen<>("Apple", 3);
		PairGen<String, Integer> p2 = new PairGen<>("Apple", 3);
		System.out.println(CompareGen.compare(p1, p2));
		PairGen<String, String> p3 = new PairGen<>("°´Ã¼ÁöÇâ", "Java");
		PairGen<String, String> p4 = new PairGen<>("°´Ã¼ÁöÇâ", "C++");
		System.out.println(CompareGen.compare(p3, p4));
	}
}

class PairGen<K, V>{
	
	K key;
	V value;
	
	public PairGen(K key, V value) {
		this.key = key;
		this.value = value;
	}
	
	public K getkey() {
		return key;
	}
	
	public V getvalue() {
		return value;
	}
	
}

class CompareGen {
	public static <K, V> boolean compare(PairGen<K,V> c1, PairGen<K,V> c2 ) {
		boolean key, value;
		key = c1.getkey().equals(c2.getkey());
		value = c2.getvalue().equals(c1.getvalue());
		return key && value;
	}
}


