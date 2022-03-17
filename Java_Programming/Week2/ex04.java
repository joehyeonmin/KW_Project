package hw2;

public class ex04 {
	public static void main(String[] args) {
		int money = 65367;
				
		System.out.println("오만원\t: " + money/50000);
		money = money % 50000;
		System.out.println("만원\t: " + money/10000);
		money = money % 10000;
		System.out.println("오천원\t: " + money/5000);
		money = money % 5000;
		System.out.println("천원\t: " + money/1000);
		money = money % 1000;
		System.out.println("오백원\t: " + money/500);
		money = money % 500;
		System.out.println("백원\t: " + money/100);
		money = money % 100;
		System.out.println("오십원\t: " + money/50);
		money = money % 50;
		System.out.println("십원\t: " + money/10);
		money = money % 10;
		System.out.println("일원\t: " + money/1);
	}
}
