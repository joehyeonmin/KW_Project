package hw6;

public class ex01 {
	public static void main(String[] args) {
		int[][] a = { { 1, 2, 3 }, { 4, 5, 6 } };
		int[][] b = { { 6, 3, 4 }, { 5, 1, 2 } };
		int[][] c = new int[2][3];
		Matrix mx = new Matrix();
		System.out.println("��� a");
		mx.printMatrix(a);
		System.out.println("��� b");
		mx.printMatrix(b);
		System.out.println("��� c");
		mx.addMatrix(a, b, c);
		mx.printMatrix(c);
		}
}

class Matrix{
	public Matrix() {
		
	}
	
	public void printMatrix(int[][] t) {
		for(int i=0; i<t.length; i++) {
			for(int j=0; j<t[i].length; j++)
				System.out.print(t[i][j] + " ");
			System.out.println();
		}
	}
	
	public void addMatrix(int[][] x, int[][] y, int[][] z) {
		
		for(int i=0; i<2; i++)
			for(int j=0; j<3; j++)
				z[i][j] = x[i][j]  + y[i][j];
		
	}
}