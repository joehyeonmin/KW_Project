package hw13;


public class ex01 {
	public static void main(String[] args) {
		showAll("FACEBOOK");
		showAll("APPLE", "MICROSOFT");
		showAll("AMAZON", "APPLE", "GOOGLE");
	
		
	}
	static void showAll(String...a) {
		Company com;
		for(int i=0; i<a.length; i++) {
			com = Company.valueOf(a[i]);
			System.out.println(com);
		}
		System.out.println("세계 기업가치 top5 중에서 " +a.length + "개 기업이 있습니다.\n");

	}	
}

enum Company{
	AMAZON(170), APPLE(165), GOOGLE(136), FACEBOOK(101), MICROSOFT(91);
	
	int money;
	private Company(int money) {
		this.money = money;
	}
	
	@Override
	public String toString() {
		return this.ordinal()+1 + "위 " + this.name() + " 기업가치 " + this.money + "조";
	}

}


