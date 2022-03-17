package hw4;

public class ex02 {
	public static void main(String[] args){ 
		Song Dancing = new Song(1978, "스웨덴", "ABBA", "Dancing Queen"); // LG에서 만든 2017년 32인치 "
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
		System.out.println(year + "년 " + country + " 국적의 " + artist + "가 부른 "+ Title);
	}
	
}