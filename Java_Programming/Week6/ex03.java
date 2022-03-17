package hw6;
import java.util.Scanner;

public class ex03 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		MonthSchedule ms = new MonthSchedule(30);
		System.out.println("이번달 스케쥴 관리 프로그램.");
		while (true) {
			System.out.print("할일(입력:1, 보기:2, 끝내기:3) >>");
			int menu = scanner.nextInt();
			switch (menu) {
			case 1: ms.input(); break;
			case 2: ms.view(); break;
			case 3: ms.finish(); return;
			default: System.out.println("잘못입력하였습니다.");
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
		System.out.print("날짜(1~" + nDays + ")?");
		int day = scanner.nextInt();
		day--;
		if(day < 0 || day >= nDays) {
			System.out.println("날짜 잘못 입력하였습니다.!");
			return;
		}
		if(days[day].get() != null) {
			System.out.print("할 일이 이미 있습니다.");
			return;
		}
		
		System.out.print("할일(빈칸없이입력)?");
		String work = scanner.next();
		
		days[day].set(work);
	}
	
	public void view() {
		System.out.print("날짜(1~" + nDays + ")?");
		int day = scanner.nextInt();
		day--;
		if(day < 0 || day >= nDays) {
			System.out.println("날짜 잘못 입력하였습니다.!");
			return;
		}
		System.out.print((day+1) + "일의 할 일은 ");
		days[day].show();
		
	}
	
	public void finish() {
		scanner.close();
		System.out.println("프로그램을 종료합니다.");
	}
	
}

class Day {
	private String work; // 하루의 할 일을 나타내는 문자열
	
	public void set(String work) { 
		this.work = work; 
	}
	
	public String get()	{ 
		return work; 
	}
	
	
	public void show() {
		if(work == null) 
			System.out.println("없습니다.");
		else 
			System.out.println(work + "입니다.");
	}
}