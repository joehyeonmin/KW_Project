package hw3;

public class ex03 {
	public static void main(String[] args) {
		char a='e';
		for(char i=a; i+1>'a'; i--) {
			for(char j='a'; j<i+1; j++)
				System.out.print(j);
			System.out.println();
		}
		
	}
}
