package hw5;

public class ex04 {
	public static void main(String[] args) {
		Circle a = new Circle(2, 3, 30);
		Circle b = new Circle(5);
		Circle c = new Circle(2, 3);
		System.out.println("�� a : " + a);
		System.out.println("�� b : " + b);
		System.out.println("�� c : " + c);
		if (a.equals(b))
		System.out.println("���� ��");
		else
		System.out.println("���� �ٸ� ��");
		if (a.equals(c))
		System.out.println("���� ��");
		else
		System.out.println("���� �ٸ� ��");
		}
}

class Circle{
	int x;
	int y;
	int r;
	
	public Circle(int r) {
		this(0,0,r);
	}
	
	public Circle(int x, int y) {
		this(x,y,5);
	}
	
	public Circle(int x, int y, int r) {
		this.x=x;
		this.y=y;
		this.r=r;
	}
	
	public String toString() {
		return "Circle(" + x + "," + y + ") ������" + r;
	}
	
	public boolean equals(Circle a) {
		if( x==a.x && y == a.y)
			return true;
		else 
			return false;
	}
	
	
}
