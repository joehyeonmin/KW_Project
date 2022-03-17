package mid1;

public class ex05 {
	public static void main(String[] args) {
		Print[] p = { new LaserPrint(100, "Laser"), 
				new ColorPrint(100, "Color")
		};
		System.out.println(p[0].runPrint(100));
		System.out.println(p[1].runPrint(100));
		System.out.println(p[0].runPrint(50));
		p[0].addPaper(200);
		System.out.println(p[0].runPrint(50));
		System.out.println(p[1].runPrint(200));
		}
}

class Print{
	int sum;
	String name;
	
	public Print(int a, String b) {
		this.sum=a;
		this.name=b;
	}
	public int runPrint(int a) {
		return sum+a;
	}
	public void addPaper(int a) {
		
	}
	
	
}

class LaserPrint extends Print{
	
	public LaserPrint(int a, String b) {
		super(a,b);
	}
	
	public int runPrint(int a) {
		return sum+a;
	}
}

class ColorPrint extends Print{
	public ColorPrint(int a, String b) {
		super(a,b);
	}
	public int runPrint(int a) {
		return sum+a;
	}
	
	
}