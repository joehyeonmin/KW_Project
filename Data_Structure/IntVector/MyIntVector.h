//2016726072 ������

class MyIntVector {
public:
	MyIntVector(size_t init_capacity = 50);
	MyIntVector(const MyIntVector& source);
	~MyIntVector();

	MyIntVector& operator=(const MyIntVector& source);
	//precondition:MyIntVector�� ���ڷ� ����
	//postcondition:���ڷ� ���� ���Ϳ� �Ȱ��� ����
	
	void operator+=(const MyIntVector& source);
	//precondition:MyIntVector�� ���ڷ� ����
	//postcondition:LHS�� RHS�� �߰�

	int& operator[](int source);
	//precondition:sourse�� ����/������ ����� �ȵ�
	//postcondition:������ ����� �����޽��� ���/�����̸� �ش簪 ����

	MyIntVector operator+(const MyIntVector& source);
	//precondition:MyIntVector�� ���ڷ� ����/size�� ���ƾ� ��
	//postcondition:size�� �ٸ��� �����޽��� ���/�����̸� �� MyIntVector�� ��ģ ���� ����

	MyIntVector operator-(const MyIntVector& source);
	//precondition:MyIntVector�� ���ڷ� ����/size�� ���ƾ� ��
	//postcondition:size�� �ٸ��� �����޽��� ���/�����̸� �� MyIntVector�� �� ���� ����

	double operator*(const MyIntVector& source);
	//precondition:MyIntVector�� ���ڷ� ����/size�� ���ƾ� ��
	//postcondition:size�� �ٸ��� �����޽��� ���/�����̸� �� MyIntVector�� ���� �� ����

	MyIntVector operator-();
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:�����͸� ��� ������ ����

	bool operator==(const MyIntVector& source);
	//precondition:������ MyIntVector �ΰ��� ��
	//postcondition:������ true ��ȯ, �ٸ��� false ��ȯ

	MyIntVector& operator()(int x);
	//precondition:������ MyIntVector�� ���밡��/x�� ���ڷ� ����
	//postcondition:��� x ������ ����

	void pop_back();
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:������ ������ ����

	void push_back(int x);
	//precondition:������ MyIntVector�� ���밡��/x�� ���ڷ� ����
	//postcondition:x�� MyIntVector�� �������� �߰�

	size_t capacity() const { return c; }
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:c�� ��ȯ

	size_t size() const { return s; }
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:s�� ��ȯ

	void reserve(size_t n);
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:c�� n���� ����

	bool is_empty() const;
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:���������(s=0) true��ȯ, �ƴϸ� false��ȯ

	void clear();
	//precondition:������ MyIntVector�� ���밡��
	//postcondition:��� ����

private:
	int* data;
	size_t c;
	size_t s;

};