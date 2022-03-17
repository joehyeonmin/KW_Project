package hw3;

public class ex01 {
	public static void main(String[] args) {
		int eight=0;
		int nine=0;
		for(int i=1; i<100; i++) {
			if(i%8==0 && i%9==0)
				break;
			else if(i%8==0)
				eight = eight + 1;
			else if(i%9==0)
				nine = nine +1;
			
		}
		System.out.println("8의배수:"+eight+"개");
		System.out.println("9의배수:"+nine+"개");
	}
}
