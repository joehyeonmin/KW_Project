//2016726072 조현민

class MyIntVector {
public:
	MyIntVector(size_t init_capacity = 50);
	MyIntVector(const MyIntVector& source);
	~MyIntVector();

	MyIntVector& operator=(const MyIntVector& source);
	//precondition:MyIntVector를 인자로 받음
	//postcondition:인자로 받은 백터와 똑같이 만듦
	
	void operator+=(const MyIntVector& source);
	//precondition:MyIntVector를 인자로 받음
	//postcondition:LHS에 RHS를 추가

	int& operator[](int source);
	//precondition:sourse를 받음/범위를 벗어나면 안됨
	//postcondition:범위를 벗어나면 오류메시지 출력/정상이면 해당값 리턴

	MyIntVector operator+(const MyIntVector& source);
	//precondition:MyIntVector를 인자로 받음/size가 같아야 함
	//postcondition:size가 다르면 오류메시지 출력/정상이면 두 MyIntVector를 합친 벡터 리턴

	MyIntVector operator-(const MyIntVector& source);
	//precondition:MyIntVector를 인자로 받음/size가 같아야 함
	//postcondition:size가 다르면 오류메시지 출력/정상이면 두 MyIntVector를 뺀 벡터 리턴

	double operator*(const MyIntVector& source);
	//precondition:MyIntVector를 인자로 받음/size가 같아야 함
	//postcondition:size가 다르면 오류메시지 출력/정상이면 두 MyIntVector의 내적 값 리턴

	MyIntVector operator-();
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:데이터를 모두 음수로 변경

	bool operator==(const MyIntVector& source);
	//precondition:적절한 MyIntVector 두개를 비교
	//postcondition:같으면 true 반환, 다르면 false 반환

	MyIntVector& operator()(int x);
	//precondition:적절한 MyIntVector에 적용가능/x를 인자로 받음
	//postcondition:모두 x 값으로 변경

	void pop_back();
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:마지막 데이터 삭제

	void push_back(int x);
	//precondition:적절한 MyIntVector에 적용가능/x를 인자로 받음
	//postcondition:x를 MyIntVector의 마지막에 추가

	size_t capacity() const { return c; }
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:c를 반환

	size_t size() const { return s; }
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:s를 반환

	void reserve(size_t n);
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:c를 n으로 변경

	bool is_empty() const;
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:비어있으면(s=0) true반환, 아니면 false반환

	void clear();
	//precondition:적절한 MyIntVector에 적용가능
	//postcondition:모두 삭제

private:
	int* data;
	size_t c;
	size_t s;

};