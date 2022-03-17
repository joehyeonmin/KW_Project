package hw5;

public class ex03 {
	public static void main(String[] args) {
		String text1 = "eW";
		String text2 = "LOVE";
		String text3 = "C++";
		String text4 = "	programming. ";
		StringBuilder text5 = new StringBuilder(text1);
		text5.reverse();
		text5.append(' ').append(text2.toLowerCase());
		text5.append(' ').append(text3);
		text5.replace(8,11,"JAVA");
		text5.append(' ').append(text4.trim());
		System.out.println(text5.toString());
	}
}
