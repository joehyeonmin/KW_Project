package hw7;

public class ex03 {
	public static void main(String[] args) {
		Shape[] arr = { new Circle("Circle", 5),
		new Rectangle("Rectangle", 3, 4),
		new Triangle("Triangle", 5, 5)
		};
		double sum = 0;
		
		for (Shape a : arr) {
			System.out.println(a.getName() + "면적 : " + a.getArea());
			sum += a.getArea();
		}
	
		System.out.println("면적의 합 : " + sum);
		}
}

class Shape{
	private String name;
	
	public Shape(String name){
		this.name = name;
	}
	
	String getName() {
		return name;
	}
	
	double getArea() {
		return 0;
	}
}

class Circle extends Shape{
	private int radius;
	
	public Circle(String name, int radius){
		super(name);
		this.radius=radius;
	}
	
	public double getArea() {
		return 3.14* radius * radius;
	}
}

class Rectangle extends Shape{
	private int w;
	private int h;
	
	public Rectangle(String name, int w, int h) {
		super(name);
		this.w=w;
		this.h=h;
	}
	
	public double getArea() {
		return w*h;
	}
}


class Triangle extends Shape {
	double w;
	double h;
	
	public Triangle(String name, int w, int h) {
		super(name);
		this.w=w;
		this.h=h;
	}
	
	public double getArea() {
		return w*h/2;
	}
}

