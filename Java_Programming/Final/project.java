package final1;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class project
{
	public static void main( String[] args ) // �����Լ�
	{
		
		String atomname =" ";
		int atomweight = 0;
		String a;
		int b;
		List<Atom> list = new ArrayList<>();
		
		Iterator<Atom> itr = list.iterator();
		
		double comp1 = 0.0, comp2 = 0.0;
		
		
		
		System.out.println("******���ʸ�, �������̽� ����*******"); //����
	
		Storage<Atom> storage = new StorageAtom<>(100);
	    storage.add(new Atom("�����׽�Ʈ1", 50), 0);
	    storage.add(new Atom("�����׽�Ʈ2", 60), 1);
	    storage.add(new Atom("�����׽�Ʈ3", 70), 2);
	    storage.add(new Atom("�����׽�Ʈ4", 80), 3);
	    storage.add(new Atom("�����׽�Ʈ5", 90), 4);
	    
	    for(int i=0; i<5; i++) {
	    	
	    	Atom temp6 = storage.get(i);
	    	System.out.println(temp6);
	    }
	    System.out.println("******************************");
	    System.out.println();
		
	    while(true) { //�������� ���α׷� ����
			System.out.println("�ֱ���ǥ 1~20�� ���� ���� ���α׷��Դϴ�"); 
			System.out.println("******************************");
			System.out.println("���Ͻô� ��ȣ�� �������ּ���");
			System.out.println("******************************");
			System.out.println("1. ���� ���� ����Ʈ ���");
			System.out.println("2. ���ο� ���� �߰� ");
			System.out.println("3. ���� �˻�");
			System.out.println("4. ���� ũ�� ��");
			System.out.println("5. �߰��� ���� ����");
			System.out.println("6. ���α׷� ����");
			System.out.println("******************************");
			
			Scanner scanner = new Scanner(System.in);
			int menu = scanner.nextInt();
									
			switch (menu) {
				case 1: //���� ���� ����Ʈ ���
					System.out.println("���� ���� ����Ʈ�� ����մϴ�.");
					for(AtomNum type : AtomNum.values()){
			            System.out.println(type); 
			        }
										
					System.out.println("***********�߰��� ����***********");
										
					list.forEach((temp) -> {
						System.out.println(temp);
					});
				
					
					System.out.println("******************************");
					
					continue;
				
				case 2: //���ο� ���� �߰�
									
					Scanner sc2 = new Scanner(System.in);
					System.out.println("�߰��� ���� �̸��� �Է����ּ���.");
					a = sc2.nextLine();
					
					System.out.println("�߰��� ������ ���Ը� �Է����ּ���.");
					b = sc2.nextInt();
					
					atomname =a;
					atomweight = b;
					list.add(new Atom(atomname, atomweight));
														
					System.out.println("���ο� ���Ұ� �߰��Ǿ����ϴ�.");
					System.out.println("******************************");
					continue;
								
				case 3: //���� �˻�
					 
					Scanner sc3 = new Scanner(System.in);
					System.out.println("�������ּ���(1~20��) : 1.������ �̸� 2. ������ ����");
					int choose = sc3.nextInt();
					
					if (choose == 1) {
						System.out.println("������ �̸��� �Է����ּ���.");
						String inputatomname = sc3.next();
							
						for (AtomNum c : AtomNum.values()) {
							if (c.name().equals(inputatomname)) {
						        System.out.println(inputatomname + "");
						        continue;
						    }
						}
										
						AtomNum com;
						com = AtomNum.valueOf(inputatomname);
						System.out.println(com);
						
						System.out.println("******************************");
						continue;
					}
										
					else if(choose == 2) {
						System.out.println("������ ���Ը� �Է����ּ���");
						double inputatomweight = sc3.nextDouble();
						
						
						for (AtomNum c : AtomNum.values()) {
					        if (c.getsize() == inputatomweight) {
					        	System.out.println(c.name() + "���Դ� " +inputatomweight + "�Դϴ�.");
					        	break;
					        }
					    }
						continue;
					}
					
					else {
						System.out.println("�߸��Է��ϼ̽��ϴ�.");
						continue;
					}
					
				case 4: //���� ũ�� ��
					
					System.out.println("���� �� ���Ҹ� �Է����ּ���(1~20��).");
					System.out.print("ù��° ���� : ");
					String compareatomname1 = scanner.next();
					
					
					System.out.print("�ι�° ���� : ");
					String compareatomname2 = scanner.next();
					
					int temp = 0;
										
					AtomNum temp1 = AtomNum.valueOf(compareatomname1);
					for(AtomNum type : AtomNum.values()){
						if(type == temp1 ) {
							comp1 = temp1.getsize();
						
							temp = 1;
						}
					}	
						if(temp == 0) {
							System.out.println("����Ʈ�� �����ϴ�.");
							break;
						}
			        
					temp = 0;
					AtomNum temp2 = AtomNum.valueOf(compareatomname2);
					for(AtomNum type : AtomNum.values()){
						if(type == temp2 ) {
							comp2 = temp2.getsize();
							temp = 1;
						}
					}
						
					if(temp == 0) {
						System.out.println("����Ʈ�� �����ϴ�.");
						break;
					}
			        
					
					if(comp1 > comp2)
						System.out.println(compareatomname1 + "�� ���԰� �� Ů�ϴ�.");
					
					else if(comp1 < comp2)
						System.out.println(compareatomname2 + "�� ���԰� �� Ů�ϴ�.");
					
					else
						System.out.println("���԰� �����ϴ�.");
					
					
					System.out.println("******************************");
					continue;
								
				case 5: //�߰��� ���� ����
					System.out.println("�߰��� ���Ҹ� � ������ �����Ͻðڽ��ϱ�?");
					System.out.println("1.�̸���  2.���Լ�");
					System.out.print("�Է� : ");
					int setatom = scanner.nextInt();
					if(setatom == 1) {
						Collections.sort(list, (i,j) -> i.name.compareTo(j.name));
						
						System.out.println("**********������ �Ϸ�Ǿ����ϴ�************");
					}
					else if(setatom == 2) {
						Collections.sort(list, (i,j) -> (int)i.weight-(int)j.weight);
					
						System.out.println("**********������ �Ϸ�Ǿ����ϴ�************");
						
					}
					else
						System.out.println("�߸��Է��ϼ̽��ϴ�.");
														
					continue;
				
				
				case 6: //���α׷� ����
					System.out.println("���α׷��� �����մϴ�.");
					break;
				
				default: 
					System.out.println("�߸��Է��Ͽ����ϴ�.");
					continue;
					
			}
			
			break;	
		}
	}
}

enum AtomNum{
			����(1.0079),
			���(4.0026),
			��Ƭ(6.941),
			������(9.0121),
			�ؼ�(10.811),
			ź��(12.0107),
			����(14.0067),
			���(15.9994),
			�÷����(20.1797),
			�׿�(20.1797),
			��Ʈ��(22.9897),
			���׳׽�(24.3050),
			�˷�̴�(26.9815),
			�Լ�(28.0855),
			��(30.9737),
			Ȳ(32.065),
			����(35),
			�Ƹ���(39.948),
			Į��(39.0983),
			Į��(40.078);
			
			public double size;
			AtomNum(double size) {
				this.size = size;
			}
			
			public double getsize() {
				return size;
			}
			
			public String Aname;
			AtomNum(String Aname) {
				this.Aname = Aname;
			}
			
			
			public String getAname() {
				return Aname;
			}
			
			@Override
			public String toString() {
				return this.ordinal()+1 + "�� " + this.name() + " ������ ���Դ� " + this.size + "�̴�";
			}
}

class Atom { //���� �Է¹��� ���� ������ Ŭ����
	String name;
	double weight;
	public Atom(String name, double weight) {
		this.name = name; this.weight = weight;
	}
		
	String getName() {
		return name;
	}
		
	double getweight() {
		return weight;
	}
		
	public String toString() 
	{ 
		return name + " : " + weight; 
	}
	
	
}

interface Storage<T> { //���ʸ� �������̽� ����
    public void add(T item, int index);
 
    public T get(int index);
}

class StorageAtom<T> implements Storage<T> {
	 
    private T[] array;
 
    public StorageAtom(int capacity) {
        this.array = (T[]) (new Object[capacity]);
    }
 
    @Override
    public void add(T item, int index) {
        array[index] = item;
    }
 
    @Override
    public T get(int index) {
        return array[index];
    }
 }





