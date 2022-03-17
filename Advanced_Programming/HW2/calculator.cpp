*
  calculator_buggy.cpp
*/

#include "std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) { }
	Token(char ch, double val) : kind(ch), value(val) { }
	Token(char ch, string n) : kind(ch), name(n) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() : full(0), buffer(0) { }
	
	Token get();
	void putback(Token t) { buffer = t; full = true; }//����
	
	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqrt_t = 'q'; //�߰�
const string sqrt_s = "sqrt"; //�߰�
const char sin_t = 's';//�߰�
const string sin_s = "sin";//�߰�
const char cos_t = 'c';//�߰�
const string cos_s = "cos";//�߰�
const char tan_t = 't';//�߰�
const string tan_s = "tan";//�߰�


Token Token_stream::get() //����
{
	if (full == true) { full = false; return buffer; }//����
	char ch;
	cin >> ch;
	switch (ch) {
	case '(': 
	case ')':
	case '+': 
	case '-': 
	case '*':
	case '/': 
	case '%':
	case ';': 
	case '=':
	case '^'://�߰�
		return Token(ch);
	case '.': 
	case '0': 
	case '1': 
	case '2': 
	case '3':
	case '4':
	case '5': 
	case '6': 
	case '7': 
	case '8': 
	case '9':
	{
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") return Token(quit);
			if (s == sqrt_s) return Token(sqrt_t);//�߰�
			if (s == sin_s) return Token(sin_t);//�߰�
			if (s == cos_s) return Token(cos_t);//�߰�
			if (s == tan_s) return Token(tan_t);//�߰�
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c) 
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) : name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s) 
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d) 
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	//error("set: undefined name ", s); ����
	names.push_back(Variable(s, d));//�߰�
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary() 
{
	Token t = ts.get();
	switch (t.kind) {
	case '(': 
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d; //�߰�
	}
	case '-':
		return -primary();

	case '+':  //�߰�
		return primary(); //�߰�

	case number:
		return t.value;

	case name:
		if (!is_declared(t.name)) //�߰�
			error("error");
		return get_value(t.name);

	

	default:
		error("primary expected");
	}
}

double exponentiation() //�߰�(���������� *, / ���� �켱���� ����)
{ 
	double base = primary(); //base^right ����
	
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
			case '^': //������'^'���̽�
			{
				double right = expression(); //�����ʺ��� ���
				return pow(base, right); // ���� ���
				t = ts.get(); 
				break; //�Ϸ��� while�� Ż��
			}
			default: 
				ts.putback(t);  //�о��ȴ� t�� �ٽ� ����     
				return base; 
		}

	}
}

double term() 
{
	double left = exponentiation();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= exponentiation();
			break;
		case '/': 
		{
			double d = exponentiation();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.putback(t); //�߰�
			return left;
		}
	}
}


double expression() 
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t); //�߰�
			return left;
		}
	}
}

double declaration() 
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double square_oper()//�߰�
{
	double d = expression(); 
	if (d < 0) error("����� �Է����ּ���");
	return sqrt(d);
}

double sin_oper()//�߰�
{
	double d = expression();
	return sin(d);
}

double cos_oper()//�߰�
{
	double d = expression();
	return cos(d);
}

double tan_oper()//�߰�
{
	double d = expression();
	return tan(d);
}


double statement() 
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case sqrt_t://�߰�
		return square_oper();
	case sin_t://�߰�
		return sin_oper();
	case cos_t://�߰�
		return cos_oper();
	case tan_t://�߰�
		return tan_oper();
	default:
		ts.putback(t);
		return expression();
	}
}

void clean_up_mess() 
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

double const pi = 3.14159; //�߰�
double const nalog = 2.71828;  //�߰�


void calculate() 
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try {
	set_value("pi", pi);//�߰�
	set_value("e", nalog);//�߰�
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "exception\n";
	keep_window_open();
	return 2;
}
