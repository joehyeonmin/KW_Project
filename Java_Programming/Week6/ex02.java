package hw6;
import java.util.Scanner;

public class ex02 {
	public static void main(String[] args) {
		System.out.println("�ѿ� �ܾ� �˻� ���α׷��Դϴ�.");
		Scanner sc = new Scanner(System.in);
		while(true) {
			System.out.print("�ѱ� �ܾ�?");
			String kor = sc.nextLine();
			if(kor.equals("�׸�"))
				break;
			
			String eng = Dictionary.kor2Eng(kor);
			if(eng == null)
				System.out.println(kor + "�� ���� ������ �����ϴ�.");
			
			else
				System.out.println(kor + "�� " +eng);
		}
		sc.close();
	}
		
}

class Dictionary {
	private static String [] kor =
	{ "���", "�Ʊ�", "��", "�̷�", "���" };
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