package hw2;

public class ex04 {
	public static void main(String[] args) {
		int money = 65367;
				
		System.out.println("������\t: " + money/50000);
		money = money % 50000;
		System.out.println("����\t: " + money/10000);
		money = money % 10000;
		System.out.println("��õ��\t: " + money/5000);
		money = money % 5000;
		System.out.println("õ��\t: " + money/1000);
		money = money % 1000;
		System.out.println("�����\t: " + money/500);
		money = money % 500;
		System.out.println("���\t: " + money/100);
		money = money % 100;
		System.out.println("���ʿ�\t: " + money/50);
		money = money % 50;
		System.out.println("�ʿ�\t: " + money/10);
		money = money % 10;
		System.out.println("�Ͽ�\t: " + money/1);
	}
}
