package hw4;

public class ex01 {
	public static void main(String[] args){ 
		TV myTV = new TV("LG", 2017, 32); // LG���� ���� 2017�� 32��ġ "
	    myTV.show(); }
}

class TV{
	String name;
	int year;
	int size;
	
	public TV(String n, int y, int s) {
		name = n;
		year = y;
		size = s;
	}
		
	public void show() {
		System.out.println(name + "���� ���� " + year + "���� " + size + "��ġTV");
	}
	
}