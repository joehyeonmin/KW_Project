package hw4;

public class ex05 {
	public static void main(String args[]) {
		Calc c = new Calc();
		c.setValue(2, 5, '+');
		c.result();
		c.setValue(2, 5, '$');
		c.result();
		c.setValue(2, 5, '-');
		c.result();
		c.setValue(2, 5, '*');
		c.result();
		c.setValue(2, 5, '/');
		c.result();
	}
}

class Calc{
	int x;
	int y;
	char operator;
	
	public Calc() {}
			
	public void setValue(int a, int b, char o) {
		x=a;
		y=b;
		operator=o;
	}
	
	public void result() {
		switch(operator) {
		case '+': 
			System.out.println("result = " + add());
			break;
		case '-':
			System.out.println("result = " + sub());
			break;
		case '*':
			System.out.println("result = " + mul());
			break;
		case '/':
			System.out.println("result = " + div());
			break;
		default:
			System.out.println("잘못된 연산자입니다.");
		}
	}
	
	public int add() {
		return x+y;
	}
	
	public int sub() {
		return x-y;
	}
	
	public int mul() {
		return x*y;
	}
	
	public int div() {
		return x/y;
	}
	
	
	

	
}