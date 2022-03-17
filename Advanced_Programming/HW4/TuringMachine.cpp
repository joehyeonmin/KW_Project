#include "TuringMachine.h"
#include <iostream>


using namespace Turing;

Transition::Transition(const std::string& curr_s, char read_s, char write_s, Move m, const std::string& next_s)
	: curr_state{ curr_s }, read_symbol{ read_s }, write_symbol{ write_s }, move{ m }, next_state{ next_s }
{
}

Table::Table()
{

}

Table::~Table()
{

}


void Transition::print(std::ostream& os) const
{
	os << curr_state << " ";
	os << read_symbol << " ";
	os << write_symbol << " ";
	os << (move == Move::LEFT ? 'l' : (move == Move::RIGHT ? 'r' : '*')) << " ";
	os << next_state;
}

void Table::addTransition(const std::string& curr_s, char read_s, char write_s, Move move, const std::string& next_s)
{
	Transition a(curr_s, read_s, write_s, move, next_s); //Trasition 구조체멤버 사용
	rules.push_back(a); // vector line에 저장

}

void Table::print(std::ostream& os) const
{
	for (int i = 0;i < rules.size();i++) { //모두 출력
		os << "[" << i << "]: ";
		rules[i].print(os);
		os << std::endl;

	}
}

void Table::clear()
{
	rules.clear();
}

Transition* Table::findTransition(const std::string& curr_s, char read_s) 
{

	for (int i = 0; i < rules.size(); i++) // 둘다 같은게 있으면 출력
	{

		if (rules[i].getCurrState() == curr_s && rules[i].getReadSymbol() == read_s)
		{
			return &rules[i];
		}

	}

	for (int i = 0; i < rules.size(); i++) //읽은것이 다르면 읽은 내용이 '*'이거나 테이블에 있는 값이 '*'이면 출력
	{

		if (rules[i].getCurrState() == curr_s && rules[i].getReadSymbol() != read_s && (read_s == '*' || rules[i].getReadSymbol() == '*'))
		{
			return &rules[i];
		}

	}

	return nullptr;
}



void Table::initialize(const std::string& rule_script)
{
	std::vector<std::string> all_lines; //저장할 vector 선언
	std::vector<std::string> cut_line;

	all_lines = Util::split(rule_script, '\n'); //util.h의 split함수 이용

	for (int i = 0; i < all_lines.size(); i++)
	{
		std::string one_line;

		one_line = Util::stripComment(all_lines[i]); // 0부터 ; 까지 추출(util.h의 stripComment 사용)


		if (Util::isWhiteLine(one_line) == false)
		{
			cut_line = Util::split(one_line, ' '); // 0부터 ' ' 까지 자름
			char temp = cut_line[3][0]; // 0번째 원소를 가져옴
			Move tmove = Move::NONE;
			if (temp == 'l') tmove = Move::LEFT;
			if (temp == 'r') tmove = Move::RIGHT;

			addTransition(cut_line[0], cut_line[1][0], cut_line[2][0], tmove, cut_line[4]);
		}
	}


}


bool Table::load(const std::string& path) // load beaver_4.txt load bin_dec.txt
{
	std::ifstream in;   //파일 열기
	in.open(path);
	if (!in.is_open())
	{
		return false;
	}

	std::string line;
	std::string rule_copy = "";

	while (getline(in, line))
	{
		if (Util::isWhiteLine(line))
			continue;

		rule_copy = rule_copy + (line + '\n');

	}

	initialize(rule_copy);

	in.close();


	return true;

}

void Tape::initialize(const std::string& s) //강의내용
{
	sz = s.size();
	space = s.size();
	elem = new char[sz]; //연산자 new를 사용하여 char형 데이터 sz개 
	std::copy(s.begin(), s.end(), elem);

}

void Tape::print(std::ostream& os) const
{
	for (int i = 0;i < sz;i++)
		os << elem[i];
}


bool Tape::read(int i, char& c) const
{
	if (i >= 0 && i < sz) {
		c = elem[i];
		return true;
	}
	return false;
}

bool Tape::write(int i, char c)
{
	if (c == '*') // 먼저 확인 WILDCARD_SYMBOL은 상태유지
	{
		return true;
	}

	if (i >= 0 && i < sz) {
		elem[i] = c;
		return true;
	}

	
	return false;
}


void Tape::clear()
{
	sz = 0;
}


void Tape::push_back(char c) //강의내용
{
	if (sz == 0)
		reserve(5);
	else if (sz == space)
		reserve(2 * space);

	elem[sz] = c;
	++sz;

}

void Tape::push_front(char c)
{
	if (sz == 0)
		reserve(5);
	else if (sz == space)
		reserve(2 * space);

	for (int i = sz - 1; 0 <= i; i--)
	{
		elem[i + 1] = elem[i];
	}
	elem[0] = c;
	++sz;
}




Tape::Tape(const Tape& t) :sz{ t.sz }, space{ t.space }, elem{ new char[t.sz + 1] } //강의내용 //새로운 공간 할당(sz만큼)
{
	for (int i = 0; i < sz; ++i) //같은 타입의 객체를 복사
	{
		elem[i] = t.elem[i];
	}
}

Tape::Tape(Tape&& t) :sz{ t.sz }, space{ t.space }, elem{ t.elem } //강의내용 t의 sz와 elem 복사
{
	t.sz = 0; //t객체의 값을 초기화
	t.space = 0;
	t.elem = nullptr;
}

Tape& Tape::operator=(const Tape& t)//강의내용 copy and swap 
{
	//공간확인
	if (this == &t) return *this; //t=t -> no work needed

	if (t.sz <= space)
	{
		for (int i = 0; i < t.sz; i++) elem[i] = t.elem[i];
		sz = t.sz;
		return *this;
	}
	//copy&swap	
	char* p = new char[t.sz]; // 새로운 공간 할당
	for (int i = 0; i < t.sz; ++i) p[i] = t.elem[i]; //가져오기
	delete[] elem; //기존의 메모리공간 삭제
	sz = t.sz; //다시 정의
	space = t.space;
	elem = p;

	return *this; // 자신을 가리키는 포인터
}


Tape& Tape::operator=(Tape&& t) //강의내용 move
{
	delete[] elem;
	space = t.space;  //copy와 동일
	sz = t.sz;
	elem = t.elem;
	t.elem = nullptr;
	t, space = 0;
	t.sz = 0;
	return *this; //자기 자신의 주소 리턴
}


void Tape::reserve(int newalloc) //강의내용 할당된 메모리 크기 변경
{
	if (newalloc <= space) return; //추가작업 필요x
	char* p = new char[newalloc]; // newalloc만큼 복사
	for (int i = 0; i < sz; ++i) p[i] = elem[i]; //저장되어 있는만큼만 복사
	for (int k = sz; k < newalloc; ++k) p[k] = 0;
	delete[] elem;
	elem = p;
	space = newalloc;

}

void Tape::resize(int newsize)//강의내용
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) elem[i] = 0; // 늘어난 크기만큼 0으로 초기화
	sz = newsize;

}

int Tape::size() const
{
	return sz;
}

int Tape::capacity() const
{
	return space;
}

void Machine::initTape(const std::string& initial_symbols)
{
	tape.initialize(initial_symbols);
}

void Machine::initTable(const std::string& rule_script)
{
	table.initialize(rule_script);
}

bool Machine::loadTable(const std::string& path)
{
	if (table.load(path))
	{
		return true;
	}
	return false;


}

void Machine::start(const std::string& start_state, const std::string& accept_state, const std::string& reject_state)
{
	current_state = start_state;
	Machine::accept_state = accept_state;
	Machine::reject_state = reject_state;

	current_mode = Mode::NORMAL;


	current_pos = 0;
}

bool Machine::step() // init_table palindrome init_tape 11100111 start 0 halt-accept halt-reject
{
	//현재 상태와 현재심볼을 바탕으로 table에 있는 규칙을 찾고 그 규칙을 바탕으로
	//현재 테잎에 새로운 심볼을 쓰고 현재 헤드위치를 이동시키고 현재 상태값을 갱신

	char now;
	tape.read(current_pos, now); // 현재위치값으로 tape의 값 찾기
	Transition* transition = table.findTransition(current_state, now); //위치값과 tape값으로 테이블에서 규칙 찾기
	
	tape.write(current_pos, transition->getWriteSymbol());
	current_state = transition->getNextState();
	
	if (transition->getNextState() == accept_state)
	{
		current_mode = Mode::ACCEPT;
		return false;
	}

	if (transition->getNextState() == reject_state)
	{
		current_mode = Mode::REJECT;
		return false;

	}

	/*if (transition->getNextState() == error)
	{
		return false;

	}
	*/
	
		

	if (transition->getMove() == Move::LEFT)
	{
		if (current_pos == 0) // tape 왼쪽 끝에 위치
		{
			tape.push_front('_');
			current_pos = 0;
		}
		else
			current_pos--;
			
	}
		
	if (transition->getMove() == Move::RIGHT)
	{
		if (current_pos == tape.size() -1) //tape 오른쪽 끝에 위치
		{
			tape.push_back('_');
			current_pos = tape.size() - 1;
		}
		else
			current_pos++;
	}
		
	if ((char)transition->getMove() == '*')
	{
			return true;
	}

	
	return true;

}
	

