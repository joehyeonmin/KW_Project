package hw3;

public class ex05 {
	public static void main(String[] args) {
		for(int i=0; i<6; i++)
			System.out.println("f("+i+")="+func(i));
	}
		
		
	public static int func(int num) {
		if(num==0)
			return 1;
		else
			return 2*func(num-1)+1;
	}
}
