package mid1;

public class ex03 {
	public static void main(String[] args) {
		StringBuffer sb = new StringBuffer("Hello Java!");
		System.out.println("�뷮: " + sb.capacity());
		System.out.println("����: " +sb.length());
		System.out.println("�߰�: " +sb.append("!!!!"));
		System.out.println("����: " +sb.insert(6, "C++ & " ));
		System.out.println("����: " +sb.delete(6,21));
		System.out.println("�뷮: " +sb.capacity());
		System.out.println("����: " +sb.length());
		System.out.println("�뷮: " +sb.capacity());
		System.out.println("����: " +sb.length());
	}
}
