package hw7;

public class ex01 {
	public static void main(String[] args) {
		ColorPoint cp = new ColorPoint(5, 5, "Yellow");
		cp.setXY(10, 20);
		cp.setColor("Red");
		String str = cp.toString();
		System.out.println(str + "입니다.");
		}
}

class Point {
	private int x, y;
	
	public Point(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public int getX() { return x; }
	public int getY() { return y; }
	
	protected void move(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

class ColorPoint extends Point{
	String color;
	
	public ColorPoint(int x, int y, String z) {
		super(x,y);
		this.color = z;
	}
	
	public void setXY(int x, int y) {
		move(x,y);
	}
	
	public void setColor(String z) {
		this.color = z;
	}
	
	public String toString() {
		return color + "색의 (" + getX() + "," + getY() + ")의 점 ";
	}
}

