package mid1;

public class ex02 {
	public static void main(String[] args) {
		int[] a = { 5, 4, 3, 2, 1 };
		int[] b = { 3, 2, 1, 0, -1 };
		int[] p = sub(a, b);
		
		System.out.print("A - B = { " + p[0]);
		
		for (int i = 1; i < p.length; i++)
			System.out.print(", " + p[i]);
		
		System.out.print(" }");
		}

	private static int[] sub(int[] x, int[] y) {
		int[] c= {0,0,0,0,0};
		for (int i=0; i<5; i++) {
			if(x[0] !=  y[i])
				c[0]=x[0];
			
		}
		for (int i=0; i<5; i++) {
			if(x[i] !=  y[1])
				c[1]=x[1];
		}
		for (int i=0; i<5; i++) {
			if(x[i] ==  y[2])
				c[2] = x[2];
		}
		for (int i=0; i<5; i++) {
			if(x[i] ==  y[3])
				c[3] =x[3];
		}
		for (int i=0; i<5; i++) {
			if(x[i] ==  y[4])
				c[4]=x[4];
		}
			
		return c;
	}

	
}

