package hw4;

public class ex02 {
	public static void main(String[] args){ 
		Song Dancing = new Song(1978, "������", "ABBA", "Dancing Queen"); // LG���� ���� 2017�� 32��ġ "
		Dancing.show(); }
}


class Song{
	
	int year;
	String country;
	String artist;
	String Title;
	
	public Song(int y, String c, String a, String t) {
		year = y;
		country = c;
		artist = a;
		Title = t;
	}
		
	public void show() {
		System.out.println(year + "�� " + country + " ������ " + artist + "�� �θ� "+ Title);
	}
	
}