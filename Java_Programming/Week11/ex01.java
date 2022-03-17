package hw11;

public class ex01 {
	public static void main(String[] args) {
		int size=10;
		GStack<String> stringStack = new GStack<String>(size);
		stringStack.push("seoul");
		stringStack.push("busan");
		stringStack.push("LA");
		
		for(int i=0; i<size; i++) {
			String str = stringStack.pop();
			if(str != null) System.out.println(str);
		}
		
		GStack<Integer> intStack = new GStack<Integer>(size);
		intStack.push(1);
		intStack.push(3);
		intStack.push(5);
		for(int i=0; i<size; i++) {
			Integer is = intStack.pop();
			if(is != null) System.out.println(is);
		}
	}
}

class GStack<T>{
	
	Object[] stck;
	int num;
	
	public GStack(int a) {
		stck = new Object[a];
	}
	
	public void push(T b) {
		if(num==stck.length)
			return;
		stck[num] = b;
		num++;
	}
	
	public T pop() {
		if(num==0)
			return null;
			
		num--;
		return (T)stck[num];
	}
}
