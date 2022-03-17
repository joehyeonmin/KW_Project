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
	Transition a(curr_s, read_s, write_s, move, next_s); //Trasition ����ü��� ���
	rules.push_back(a); // vector line�� ����

}

void Table::print(std::ostream& os) const
{
	for (int i = 0;i < rules.size();i++) { //��� ���
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

	for (int i = 0; i < rules.size(); i++) // �Ѵ� ������ ������ ���
	{

		if (rules[i].getCurrState() == curr_s && rules[i].getReadSymbol() == read_s)
		{
			return &rules[i];
		}

	}

	for (int i = 0; i < rules.size(); i++) //�������� �ٸ��� ���� ������ '*'�̰ų� ���̺� �ִ� ���� '*'�̸� ���
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
	std::vector<std::string> all_lines; //������ vector ����
	std::vector<std::string> cut_line;

	all_lines = Util::split(rule_script, '\n'); //util.h�� split�Լ� �̿�

	for (int i = 0; i < all_lines.size(); i++)
	{
		std::string one_line;

		one_line = Util::stripComment(all_lines[i]); // 0���� ; ���� ����(util.h�� stripComment ���)


		if (Util::isWhiteLine(one_line) == false)
		{
			cut_line = Util::split(one_line, ' '); // 0���� ' ' ���� �ڸ�
			char temp = cut_line[3][0]; // 0��° ���Ҹ� ������
			Move tmove = Move::NONE;
			if (temp == 'l') tmove = Move::LEFT;
			if (temp == 'r') tmove = Move::RIGHT;

			addTransition(cut_line[0], cut_line[1][0], cut_line[2][0], tmove, cut_line[4]);
		}
	}


}


bool Table::load(const std::string& path) // load beaver_4.txt load bin_dec.txt
{
	std::ifstream in;   //���� ����
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

void Tape::initialize(const std::string& s) //���ǳ���
{
	sz = s.size();
	space = s.size();
	elem = new char[sz]; //������ new�� ����Ͽ� char�� ������ sz�� 
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
	if (c == '*') // ���� Ȯ�� WILDCARD_SYMBOL�� ��������
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


void Tape::push_back(char c) //���ǳ���
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




Tape::Tape(const Tape& t) :sz{ t.sz }, space{ t.space }, elem{ new char[t.sz + 1] } //���ǳ��� //���ο� ���� �Ҵ�(sz��ŭ)
{
	for (int i = 0; i < sz; ++i) //���� Ÿ���� ��ü�� ����
	{
		elem[i] = t.elem[i];
	}
}

Tape::Tape(Tape&& t) :sz{ t.sz }, space{ t.space }, elem{ t.elem } //���ǳ��� t�� sz�� elem ����
{
	t.sz = 0; //t��ü�� ���� �ʱ�ȭ
	t.space = 0;
	t.elem = nullptr;
}

Tape& Tape::operator=(const Tape& t)//���ǳ��� copy and swap 
{
	//����Ȯ��
	if (this == &t) return *this; //t=t -> no work needed

	if (t.sz <= space)
	{
		for (int i = 0; i < t.sz; i++) elem[i] = t.elem[i];
		sz = t.sz;
		return *this;
	}
	//copy&swap	
	char* p = new char[t.sz]; // ���ο� ���� �Ҵ�
	for (int i = 0; i < t.sz; ++i) p[i] = t.elem[i]; //��������
	delete[] elem; //������ �޸𸮰��� ����
	sz = t.sz; //�ٽ� ����
	space = t.space;
	elem = p;

	return *this; // �ڽ��� ����Ű�� ������
}


Tape& Tape::operator=(Tape&& t) //���ǳ��� move
{
	delete[] elem;
	space = t.space;  //copy�� ����
	sz = t.sz;
	elem = t.elem;
	t.elem = nullptr;
	t, space = 0;
	t.sz = 0;
	return *this; //�ڱ� �ڽ��� �ּ� ����
}


void Tape::reserve(int newalloc) //���ǳ��� �Ҵ�� �޸� ũ�� ����
{
	if (newalloc <= space) return; //�߰��۾� �ʿ�x
	char* p = new char[newalloc]; // newalloc��ŭ ����
	for (int i = 0; i < sz; ++i) p[i] = elem[i]; //����Ǿ� �ִ¸�ŭ�� ����
	for (int k = sz; k < newalloc; ++k) p[k] = 0;
	delete[] elem;
	elem = p;
	space = newalloc;

}

void Tape::resize(int newsize)//���ǳ���
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) elem[i] = 0; // �þ ũ�⸸ŭ 0���� �ʱ�ȭ
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
	//���� ���¿� ����ɺ��� �������� table�� �ִ� ��Ģ�� ã�� �� ��Ģ�� ��������
	//���� ���ٿ� ���ο� �ɺ��� ���� ���� �����ġ�� �̵���Ű�� ���� ���°��� ����

	char now;
	tape.read(current_pos, now); // ������ġ������ tape�� �� ã��
	Transition* transition = table.findTransition(current_state, now); //��ġ���� tape������ ���̺��� ��Ģ ã��
	
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
		if (current_pos == 0) // tape ���� ���� ��ġ
		{
			tape.push_front('_');
			current_pos = 0;
		}
		else
			current_pos--;
			
	}
		
	if (transition->getMove() == Move::RIGHT)
	{
		if (current_pos == tape.size() -1) //tape ������ ���� ��ġ
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
	

