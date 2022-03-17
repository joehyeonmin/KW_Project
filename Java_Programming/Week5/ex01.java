package hw5;

public class ex01 {
	public static void main(String[] args) {
		String text = "I love you";
		for(int i=0; i<10; i++)
		{
			String a = text.substring(0,1);
			String b = text.substring(1,10);
			text=b+a;
			System.out.println(text);
		}
	}
}
