package hw4;

public class ex03{
	public static void main(String args[]) {
		Rectangle r = new Rectangle(2, 2, 8, 7);
		Rectangle s = new Rectangle(5, 5, 6, 6);
		Rectangle t = new Rectangle(1, 1, 10, 10);
		r.show();
		
		System.out.println("s�� ������ " + s.square());
		if (t.contains(r))
		System.out.println("t�� r�� �����մϴ�.");
		if (t.contains(s))
		System.out.println("t�� s�� �����մϴ�.");
	}
}

class Rectangle{
	
	int x;
	int y;
	int width;
	int height;
	
	public Rectangle(int a, int b, int w, int h) {
		x=a;
		y=b;
		width=w;
		height=h;
	}
		
	public int square() {
		return width * height;
	}
	
	public void show() {
		System.out.println("(" + x + "," + y + ")���� ũ�Ⱑ " + width + "x" + height + "�� �簢��");
	}
	
	public boolean contains(Rectangle r) {
		if(x<r.x && y<r.y && x+width > r.x + r.width && y+width > r.y + r.height)
			return true;
		else
			return false;
			
	}
	
	
	
}