package mid1;
import java.util.Scanner;

public class ex01 {
	public static void main(String[] args) {
		Fruit[] f = new Fruit[5];
		String name;
		int price;
		
		Scanner scan = new Scanner(System.in);
		int sum = 0;
		for (int i = 0; i < f.length; i++) {
			System.out.print(i + 1 + ">> ");
			price = scan.nextInt();
			name = scan.next();
			f[i] = new Fruit(name, price);
			sum = sum + f[i].sprice();
		}
		System.out.print("sum : " +sum);
		scan.close();
		}
}

class Fruit{
	String x;
	int y;
	
	public Fruit(String x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public int sprice() {
		return y;
	}
}