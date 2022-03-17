package hw13;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.function.*;

public class ex03 {
	public static void main(String[] args) {
		List<Integer> list = new ArrayList<>();
			
		IntSupplier is = ( ) -> { 
			Random rand = new Random();
			return rand.nextInt(100)+100;
		};
		
		list = makeRandomList(is, 10);
		System.out.println(list);
		
		IntUnaryOperator u = i -> i/100 + (i%100) / 100 + i%10;
		sumDigits(u, list);
		System.out.println(list);
		
		Predicate<Integer> p = i -> i >=10;
		list.removeIf(p);
		System.out.println(list);
	}
	
	static <T> List<Integer> makeRandomList(IntSupplier s, int size) 
	{
		List<Integer> makelist = new ArrayList<>();
		for(int i =0; i<10; i++) {
			makelist.add(s.getAsInt());
		}
		return makelist;
	}
	
	
	static void sumDigits(IntUnaryOperator u, List<Integer> list) 
	{
		for(int i =0; i<10; i++) {
			list.set(i, u.applyAsInt(list.get(i)));
		}
		
	}
	
	/*default boolean removeIf(Predicate<? super E> filter) {}
	{
		
	}*/
}