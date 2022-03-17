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
	void putback(Token t) { buffer = t; full = true; }//수정
	
	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqrt_t = 'q'; //추가
const string sqrt_s = "sqrt"; //추가
const char sin_t = 's';//추가
const string sin_s = "sin";//추가
const char cos_t = 'c';//추가
const string cos_s = "cos";//추가
const char tan_t = 't';//추가
const string tan_s = "tan";//추가


Token Token_stream::get() //수정
{
	if (full == true) { full = false; return buffer; }//수정
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
	case '^'://추가
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
			if (s == sqrt_s) return Token(sqrt_t);//추가
			if (s == sin_s) return Token(sin_t);//추가
			if (s == cos_s) return Token(cos_t);//추가
			if (s == tan_s) return Token(tan_t);//추가
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
	//error("set: undefined name ", s); 삭제
	names.push_back(Variable(s, d));//추가
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
		return d; //추가
	}
	case '-':
		return -primary();

	case '+':  //추가
		return primary(); //추가

	case number:
		return t.value;

	case name:
		if (!is_declared(t.name)) //추가
			error("error");
		return get_value(t.name);

	

	default:
		error("primary expected");
	}
}

double exponentiation() //추가(제곱연산이 *, / 보다 우선순위 높음)
{ 
	double base = primary(); //base^right 형태
	
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
			case '^': //연산자'^'케이스
			{
				double right = expression(); //오른쪽부터 계산
				return pow(base, right); // 제곱 계산
				t = ts.get(); 
				break; //완료후 while문 탈출
			}
			default: 
				ts.putback(t);  //읽어드렸던 t를 다시 삽입     
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
			ts.putback(t); //추가
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
			ts.putback(t); //추가
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

double square_oper()//추가
{
	double d = expression(); 
	if (d < 0) error("양수를 입력해주세요");
	return sqrt(d);
}

double sin_oper()//추가
{
	double d = expression();
	return sin(d);
}

double cos_oper()//추가
{
	double d = expression();
	return cos(d);
}

double tan_oper()//추가
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
	case sqrt_t://추가
		return square_oper();
	case sin_t://추가
		return sin_oper();
	case cos_t://추가
		return cos_oper();
	case tan_t://추가
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

double const pi = 3.14159; //추가
double const nalog = 2.71828;  //추가


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
	set_value("pi", pi);//추가
	set_value("e", nalog);//추가
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
