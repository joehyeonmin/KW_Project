package hw5;

public class ex02{
	public static void main(String[] args) {
		CurrencyConverter.setRate(1121);
		System.out.println("ȯ��1�޷� : " + CurrencyConverter.getRate());
		System.out.println("�鸸���� $" +
		CurrencyConverter.toDollar(1000000) + "�Դϴ�.");
		System.out.println("$120�� " +
		CurrencyConverter.toKW(120) + "�� �Դϴ�.");
	}
}

class CurrencyConverter{
	
	static int exchanged_rate;
	
	public static void setRate(int i) {
		exchanged_rate = i;
	}
	
	public static double getRate() {
		return exchanged_rate;
	}
	
	public static double toDollar(int i){
		return (double)i/(double)exchanged_rate;
	}
	
	public static double toKW(int i){
		return (double)i*(double)exchanged_rate;
		
	}
}
