package hw5;

public class ex05 {
	public static void main(String args[]) {
		ExId a = new ExId();
		ExId b = new ExId();
		ExId.setStep(3);
		ExId c = new ExId();
		ExId d = new ExId();
		System.out.println("a�� �ĺ� ��ȣ : " + a.getId());
		System.out.println("b�� �ĺ� ��ȣ : " + b.getId());
		System.out.println("c�� �ĺ� ��ȣ : " + c.getId());
		System.out.println("d�� �ĺ� ��ȣ : " + d.getId());
		ExId.setStep(1);
		int max = ExId.getMaxId();
		System.out.println("������ �ο��� �ĺ� ��ȣ : " + max);
		System.out.println("������ �ο��� �ĺ� ��ȣ : " +
		(max+ExId.getStep()));
		}
}

class ExId{
	static int count =0;
	static int step = 1;
	int id;
	
	public ExId() {
		count = count +step;
		id = count;
	}
	
	public int getId() {
		return id;
	}
	
	public static void setStep(int a) {
		step = a;
	}
	
	public static int getStep() {
		return step;
	}
	
	public static int getMaxId() {
		return count;
	}
}