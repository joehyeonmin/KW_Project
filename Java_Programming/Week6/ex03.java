package hw6;
import java.util.Scanner;

public class ex03 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		MonthSchedule ms = new MonthSchedule(30);
		System.out.println("�̹��� ������ ���� ���α׷�.");
		while (true) {
			System.out.print("����(�Է�:1, ����:2, ������:3) >>");
			int menu = scanner.nextInt();
			switch (menu) {
			case 1: ms.input(); break;
			case 2: ms.view(); break;
			case 3: ms.finish(); return;
			default: System.out.println("�߸��Է��Ͽ����ϴ�.");
			}
			System.out.println();
		}
	}
}

class MonthSchedule{
	private int nDays;
	private Day[] days;
	private Scanner scanner;
	
	public MonthSchedule(int nDays) {
		this.nDays = nDays;
		this.days = new Day[nDays];
		for(int i=0; i<nDays; i++)
			days[i]=new Day();
		scanner = new Scanner(System.in);
	}
	
	
	public void input() {
		System.out.print("��¥(1~" + nDays + ")?");
		int day = scanner.nextInt();
		day--;
		if(day < 0 || day >= nDays) {
			System.out.println("��¥ �߸� �Է��Ͽ����ϴ�.!");
			return;
		}
		if(days[day].get() != null) {
			System.out.print("�� ���� �̹� �ֽ��ϴ�.");
			return;
		}
		
		System.out.print("����(��ĭ�����Է�)?");
		String work = scanner.next();
		
		days[day].set(work);
	}
	
	public void view() {
		System.out.print("��¥(1~" + nDays + ")?");
		int day = scanner.nextInt();
		day--;
		if(day < 0 || day >= nDays) {
			System.out.println("��¥ �߸� �Է��Ͽ����ϴ�.!");
			return;
		}
		System.out.print((day+1) + "���� �� ���� ");
		days[day].show();
		
	}
	
	public void finish() {
		scanner.close();
		System.out.println("���α׷��� �����մϴ�.");
	}
	
}

class Day {
	private String work; // �Ϸ��� �� ���� ��Ÿ���� ���ڿ�
	
	public void set(String work) { 
		this.work = work; 
	}
	
	public String get()	{ 
		return work; 
	}
	
	
	public void show() {
		if(work == null) 
			System.out.println("�����ϴ�.");
		else 
			System.out.println(work + "�Դϴ�.");
	}
}