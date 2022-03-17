//2016726072 조현민

#include <iostream>
#include "MyIntVector.h"

using namespace std;

int main() {
	MyIntVector a;
	cout << "a:   " << "size:" << a.size() << " capacity:" << a.capacity() << endl;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	cout << "a:   " << "size:" << a.size() << " capacity:" << a.capacity() << endl;
	
	MyIntVector b;
	cout << "b:   " << "size:" << b.size() << " capacity:" << b.capacity() << endl;
	b.push_back(6);
	b.push_back(7);
	b.push_back(8);
	b.push_back(9);
	b.push_back(10);
	cout << "b:   " << "size:" << b.size() << " capacity:" << b.capacity() << endl;
	
	cout << "a:  ";
	for (int i = 0; i < a.size(); i++)
		cout << "[" << i << "]=" << a[i] << " ";
	cout << "\n";
		
	cout << "b:  ";
	for (int i = 0; i < b.size(); i++)
		cout << "[" << i << "]=" << b[i] << " ";
	cout << "\n";
	
	MyIntVector c;
	c = a;
	cout << "c:  ";
	for (int i = 0; i < c.size(); i++)
		cout << "[" << i << "]=" << c[i] << " ";
	cout << "\n";
	
	c += b;
	cout << "c+=b:  ";
	for (int i = 0; i < c.size(); i++)
		cout << "[" << i << "]=" << c[i] << " ";
	cout << "\n";

	cout << "c[3]=" << c[3] << "\n" << "c[8]=" << c[8] << "\n";
	// cout << c[12] << endl;

	MyIntVector d;
	d = a + b;
	cout << "d:  ";
	for (int i = 0; i < d.size(); i++)
		cout << "[" << i << "]=" << d[i] << " ";
	cout << "\n";

	MyIntVector e;
	e= a - b;
	cout << "e:  ";
	for (int i = 0; i < e.size(); i++)
		cout << "[" << i << "]=" << e[i] << " ";
	cout << "\n";

	int temp = a * b;
	cout << "a*b 내적의 결과값은 " << temp << "입니다" << "\n";

	/*MyIntVector e1 = c + a;
	cout << "e1:  ";
	for (int i = 0; i < e.size(); i++)
		cout << "[" << i << "]=" << e[i] << " ";
	cout << "\n";*/

	MyIntVector f;
	f = -c;
	cout << "f:  ";
	for (int i = 0; i < f.size(); i++)
		cout << "[" << i << "]=" << f[i] << " ";
	cout << "\n";
	
	cout << "a와 b는 같은가요? 다른가요?:  ";
	if (a == b)
		cout << "a와b는 같음" << "\n";
	else
		cout << "a와b는 다름" << "\n";
	
	MyIntVector g;
	g = a(5);
	cout << "g:  ";
	for (int i = 0; i < g.size(); i++)
		cout << "[" << i << "]=" << g[i] << " ";
	cout << "\n";
	
	g.pop_back();
	cout << "삭제된g:  ";
	for (int i = 0; i < g.size(); i++)
		cout << "[" << i << "]=" << g[i] << " ";
	cout << "\n";

	g.reserve(7);
	cout << "g:  ";
	for (int i = 0; i < g.size(); i++)
		cout << "[" << i << "]=" << g[i] << " ";
	cout << "\n";
	cout << "변화된 g의 capacity:" << g.capacity();
	cout << "\n";

	g.clear();
	cout << "클리어 된 g:  ";
	if(g.is_empty() == true)
		cout << "내용이 비워졌습니다" << "\n";
	
	return 0;
}
	
