package hw10;
import java.util.StringTokenizer;

public class ex01 {
	public static void main(String[] args) {
		String s1 = "동해물과 백두산이 마르고 닳도록";
		String s2 = "2020/11/03";
		String s3 = "2020년11월03일";


		StringTokenizer st1 = new StringTokenizer(s1);
		
		int i =0;
		System.out.println("s1 count: "+ st1.countTokens());
		while(st1.hasMoreTokens()){
			
			i++;
			System.out.println(i + " : " + st1.nextToken());
		}
		System.out.println();
		
		i=0;
		StringTokenizer st2 = new StringTokenizer(s2, "/");
		
		System.out.println("s2 count: "+ st2.countTokens());
		while(st2.hasMoreTokens()){
			
			i++;
			System.out.println(i + " : "+ st2.nextToken());
		}
		System.out.println();
		
		StringTokenizer st3 = new StringTokenizer(s3, "년월일");
		
		i=0;
		System.out.println("s3 count: "+ st3.countTokens());
		while(st3.hasMoreTokens()){
			
			i++;
			System.out.println(i +" : "+st3.nextToken());
		}
			
	}
}
