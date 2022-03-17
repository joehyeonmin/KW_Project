package mid1;

public class ex03 {
	public static void main(String[] args) {
		StringBuffer sb = new StringBuffer("Hello Java!");
		System.out.println("용량: " + sb.capacity());
		System.out.println("길이: " +sb.length());
		System.out.println("추가: " +sb.append("!!!!"));
		System.out.println("삽입: " +sb.insert(6, "C++ & " ));
		System.out.println("삭제: " +sb.delete(6,21));
		System.out.println("용량: " +sb.capacity());
		System.out.println("길이: " +sb.length());
		System.out.println("용량: " +sb.capacity());
		System.out.println("길이: " +sb.length());
	}
}
