package hw9;
import java.util.InputMismatchException;
import java.util.Scanner;

public class ex03 {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		try {
		System.out.print("x값 : ");
		int x = scan.nextInt();
		System.out.print("y값 : ");
		int y = scan.nextInt();
		System.out.println("x * y = " + mul(x, y));
		System.out.println("x / y = " + div(x, y));
		} catch(InputMismatchException e) {
			e.printStackTrace();
		} catch(ArithmeticException e) {
			e.printStackTrace();
		} finally {
			System.out.println("프로그램을 종료합니다.");
		}
	}

	private static int mul(int x, int y) {
		return x*y;
	}
	
	private static double div(int x, int y) {
		return (double)x/y;
	}
	
}

