package hw10;
import java.util.Random;

public class ex02 {
	public static void main(String[] args) {
		Random rand = new Random();
		int[] counter = new int[10];
		int[] iarr = new int[100];
		
		for(int i = 0; i<iarr.length; i++){
			iarr[i] = rand.nextInt(10);
			System.out.print(iarr[i]);
			if(i%20 ==19)
				System.out.println();
		}
		System.out.println();
		
		
		for(int i = 0; i<iarr.length; i++){
			
			counter[iarr[i]]++;
			
		}
		
		for(int i = 0; i<counter.length; i++){
			System.out.print(i+"°³¼ö\t: ");
			for(int j = 0; j<counter[i]; j++)
				System.out.print("*");
			System.out.println();
		}
		
	}
}
