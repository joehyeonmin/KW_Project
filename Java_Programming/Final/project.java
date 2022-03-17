package final1;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class project
{
	public static void main( String[] args ) // 메인함수
	{
		
		String atomname =" ";
		int atomweight = 0;
		String a;
		int b;
		List<Atom> list = new ArrayList<>();
		
		Iterator<Atom> itr = list.iterator();
		
		double comp1 = 0.0, comp2 = 0.0;
		
		
		
		System.out.println("******제너릭, 인터페이스 연습*******"); //연습
	
		Storage<Atom> storage = new StorageAtom<>(100);
	    storage.add(new Atom("원소테스트1", 50), 0);
	    storage.add(new Atom("원소테스트2", 60), 1);
	    storage.add(new Atom("원소테스트3", 70), 2);
	    storage.add(new Atom("원소테스트4", 80), 3);
	    storage.add(new Atom("원소테스트5", 90), 4);
	    
	    for(int i=0; i<5; i++) {
	    	
	    	Atom temp6 = storage.get(i);
	    	System.out.println(temp6);
	    }
	    System.out.println("******************************");
	    System.out.println();
		
	    while(true) { //원소정보 프로그램 시작
			System.out.println("주기율표 1~20번 원소 정보 프로그램입니다"); 
			System.out.println("******************************");
			System.out.println("원하시는 번호를 선택해주세요");
			System.out.println("******************************");
			System.out.println("1. 현재 원소 리스트 출력");
			System.out.println("2. 새로운 원소 추가 ");
			System.out.println("3. 원소 검색");
			System.out.println("4. 원소 크기 비교");
			System.out.println("5. 추가한 원소 정렬");
			System.out.println("6. 프로그램 종료");
			System.out.println("******************************");
			
			Scanner scanner = new Scanner(System.in);
			int menu = scanner.nextInt();
									
			switch (menu) {
				case 1: //현재 원소 리스트 출력
					System.out.println("현재 원소 리스트를 출력합니다.");
					for(AtomNum type : AtomNum.values()){
			            System.out.println(type); 
			        }
										
					System.out.println("***********추가된 원소***********");
										
					list.forEach((temp) -> {
						System.out.println(temp);
					});
				
					
					System.out.println("******************************");
					
					continue;
				
				case 2: //새로운 원소 추가
									
					Scanner sc2 = new Scanner(System.in);
					System.out.println("추가할 원소 이름을 입력해주세요.");
					a = sc2.nextLine();
					
					System.out.println("추가할 원소의 무게를 입력해주세요.");
					b = sc2.nextInt();
					
					atomname =a;
					atomweight = b;
					list.add(new Atom(atomname, atomweight));
														
					System.out.println("새로운 원소가 추가되었습니다.");
					System.out.println("******************************");
					continue;
								
				case 3: //원소 검색
					 
					Scanner sc3 = new Scanner(System.in);
					System.out.println("선택해주세요(1~20번) : 1.원소의 이름 2. 원소의 무게");
					int choose = sc3.nextInt();
					
					if (choose == 1) {
						System.out.println("원소의 이름을 입력해주세요.");
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
						System.out.println("원소의 무게를 입력해주세요");
						double inputatomweight = sc3.nextDouble();
						
						
						for (AtomNum c : AtomNum.values()) {
					        if (c.getsize() == inputatomweight) {
					        	System.out.println(c.name() + "무게는 " +inputatomweight + "입니다.");
					        	break;
					        }
					    }
						continue;
					}
					
					else {
						System.out.println("잘못입력하셨습니다.");
						continue;
					}
					
				case 4: //원소 크기 비교
					
					System.out.println("비교할 두 원소를 입력해주세요(1~20번).");
					System.out.print("첫번째 원소 : ");
					String compareatomname1 = scanner.next();
					
					
					System.out.print("두번째 원소 : ");
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
							System.out.println("리스트에 없습니다.");
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
						System.out.println("리스트에 없습니다.");
						break;
					}
			        
					
					if(comp1 > comp2)
						System.out.println(compareatomname1 + "이 무게가 더 큽니다.");
					
					else if(comp1 < comp2)
						System.out.println(compareatomname2 + "이 무게가 더 큽니다.");
					
					else
						System.out.println("무게가 같습니다.");
					
					
					System.out.println("******************************");
					continue;
								
				case 5: //추가한 원소 정렬
					System.out.println("추가한 원소를 어떤 순서로 정렬하시겠습니까?");
					System.out.println("1.이름순  2.무게순");
					System.out.print("입력 : ");
					int setatom = scanner.nextInt();
					if(setatom == 1) {
						Collections.sort(list, (i,j) -> i.name.compareTo(j.name));
						
						System.out.println("**********정렬이 완료되었습니다************");
					}
					else if(setatom == 2) {
						Collections.sort(list, (i,j) -> (int)i.weight-(int)j.weight);
					
						System.out.println("**********정렬이 완료되었습니다************");
						
					}
					else
						System.out.println("잘못입력하셨습니다.");
														
					continue;
				
				
				case 6: //프로그램 종료
					System.out.println("프로그램을 종료합니다.");
					break;
				
				default: 
					System.out.println("잘못입력하였습니다.");
					continue;
					
			}
			
			break;	
		}
	}
}

enum AtomNum{
			수소(1.0079),
			헬륨(4.0026),
			리튬(6.941),
			베릴륨(9.0121),
			붕소(10.811),
			탄소(12.0107),
			질소(14.0067),
			산소(15.9994),
			플루오린(20.1797),
			네온(20.1797),
			나트륨(22.9897),
			마그네슘(24.3050),
			알루미늄(26.9815),
			규소(28.0855),
			인(30.9737),
			황(32.065),
			염소(35),
			아르곤(39.948),
			칼륨(39.0983),
			칼슘(40.078);
			
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
				return this.ordinal()+1 + "번 " + this.name() + " 원소의 무게는 " + this.size + "이다";
			}
}

class Atom { //새로 입력받은 원자 저장할 클래스
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

interface Storage<T> { //제너릭 인터페이스 연습
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





