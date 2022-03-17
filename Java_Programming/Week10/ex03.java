package hw10;

import java.util.Arrays;

public class ex03 {
	public static void main(String[] args) {
		Circle[] c = { new Circle("Cup", 3),
			new Circle("Apple", 4),
			new Circle("Doughnut", 5),
			new Circle("Pizza", 7),
			new Circle("Ball", 2) 
		};
		Arrays.sort(c);
		for(int i=0; i<c.length; i++)
			c[i].show();
		
		int idx = Arrays.binarySearch(c,new Circle("Apple",4));
		System.out.println("Index of " + c[idx].getTitle() + " : " + idx);
	}
}

class Circle implements Comparable {
	private String name;
	private int radius;
	
	Circle(String name, int radius){
		this.name = name;
		this.radius = radius;
	}

	double getArea(){ 
		return radius * radius * 3.14;
	}
	String getTitle(){
		return name;
	}
	void show(){
		System.out.println(name + " " + getArea());
	}	
	
	@Override
	public int compareTo(Object o) {
		Circle c = (Circle)o;
		return this.radius - c.radius; 
	}	

}