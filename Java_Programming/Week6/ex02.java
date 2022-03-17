package hw6;
import java.util.Scanner;

public class ex02 {
	public static void main(String[] args) {
		System.out.println("한영 단어 검색 프로그램입니다.");
		Scanner sc = new Scanner(System.in);
		while(true) {
			System.out.print("한글 단어?");
			String kor = sc.nextLine();
			if(kor.equals("그만"))
				break;
			
			String eng = Dictionary.kor2Eng(kor);
			if(eng == null)
				System.out.println(kor + "는 저의 사전에 없습니다.");
			
			else
				System.out.println(kor + "은 " +eng);
		}
		sc.close();
	}
		
}

class Dictionary {
	private static String [] kor =
	{ "사랑", "아기", "돈", "미래", "희망" };
	private static String [] eng =
	{ "love", "baby", "money", "future", "hope" };
	
	public static String kor2Eng(String word) 
	{
		for(int i=0; i<kor.length; i++) {
			if(kor[i].equals(word))
				return eng[i];
		}
		return null;
	}
}