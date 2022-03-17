package hw3;

public class ex04 {
	public static void main(String[] args) {
		int number1 = 12321, number2 = 1232, result;
		result = palindrome(number1);
		resultPrint(number1, result);
		result = palindrome(number2);
		resultPrint(number2, result);
	}

	public static void resultPrint(int num1, int num2) {
		if (num1 == num2)
			System.out.println(num1 + "는 회문수 입니다.");
		else
			System.out.println(num1 + "는 회문수가 아닙니다.");
		}
	
	public static int palindrome(int num) {
		int temp1, temp2=0;
		while(num!=0) {
			temp1=num%10;
			num=num/10;
			temp2=temp2*10+temp1;
		}
		
		return temp2;
	}
}