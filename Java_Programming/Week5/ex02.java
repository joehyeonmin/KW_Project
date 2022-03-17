package hw5;

public class ex02{
	public static void main(String[] args) {
		CurrencyConverter.setRate(1121);
		System.out.println("환율1달러 : " + CurrencyConverter.getRate());
		System.out.println("백만원은 $" +
		CurrencyConverter.toDollar(1000000) + "입니다.");
		System.out.println("$120는 " +
		CurrencyConverter.toKW(120) + "원 입니다.");
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
