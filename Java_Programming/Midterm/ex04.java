package mid1;
import java.util.Scanner;

public class ex04 {
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		String a=scan.next();
		String b=scan.next();
		int c=scan.nextInt();
		int d=scan.nextInt();
		int e=scan.nextInt();
		int sum = c+d+e;
		System.out.print(c+" ");
		System.out.print(d+ " ");
		System.out.println(e);
		System.out.println("sum: " +sum);
		scan.close();
	}
	
}
