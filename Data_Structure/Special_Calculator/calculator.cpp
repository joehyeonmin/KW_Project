//2016726072_조현민

#include <cstdlib>
#include <iostream>
#include <stack>
#include <cstring>
#include <stdio.h>
#include <fstream>

#define SIZE 1024

using namespace std;

bool check1(char* str); // 괄호치기 확인
bool check2(char* str);
bool check3(char* str);
bool check4(char* str); // 예외처리(추가)
bool check5(char* str);

char* infixTopostfix(char* str);//인픽스를 포스트픽스로 바꿔서 리턴
int prio(char str);//연산자와 괄호의 우선순위

char calcpost(char* postresult);//포스트픽스 계산해서 출력
char txtrule(char val1, char op, char val2);//파일에서 조건 받아오기
int checknum = 0; //다른 문자르 받았을 때 처리하는 변수

int main(){

	char input[SIZE]; // 입력받은 수식을 저장하는 배열
	char* postresult; // postfix식을 저장하는 포인터

	while (true) {
		cout << "Input" << endl;
		cin >> input;

		if (input[0] == 'E' && input[1] == 'O' && input[2] == 'I')
			return 0;
		
		if (check1(input) && check2(input) && check3(input) && check4(input) && check5(input))
		{
			postresult = infixTopostfix(input);
			
			if (checknum == 0) {
				char answ = calcpost(postresult);
				cout << "Output " << endl;
				cout << answ << "\n" << endl;
			}
			else {
				checknum = checknum - 1;
				cout << "Error!" << endl;
				cout << "\n";
			}
		}
		else
		{
			cout << "Error!" << endl;
			cout << "\n";
		}
	}
}

char txtrule(char val1, char op, char val2) // 텍스트 파일에 있는 규칙을 이용하여 계산
{
	char array[SIZE];
	int position = 0;
	size_t nread;

	ifstream fileopen; //텍스트 파일을 받아서 배열에 저장
	fileopen.open("operations.txt");
	if (fileopen.is_open()) {
		while (!fileopen.eof() && position < SIZE) {
			fileopen.get(array[position]);
			position++;
		}
		array[position - 1] = '\0';
	}

	if (op == array[0]) // 텍스트 파일의 @(#,& 가능) 연산자 규칙
	{
		if (val1 == 'a' && val2 == 'a')
			return array[2];
		else if (val1 == 'a' && val2 == 'b')
			return array[4];
		else if (val1 == 'a' && val2 == 'c')
			return array[6];
		else if (val1 == 'b' && val2 == 'a')
			return array[8];
		else if (val1 == 'b' && val2 == 'b')
			return array[10];
		else if (val1 == 'b' && val2 == 'c')
			return array[12];
		else if (val1 == 'c' && val2 == 'a')
			return array[14];
		else if (val1 == 'c' && val2 == 'b')
			return array[16];
		else if (val1 == 'c' && val2 == 'c')
			return array[18];
	}
	else if (op == array[20]) // 텍스트 파일의 #(@,& 가능) 연산자 규칙
	{
		if (val1 == 'a' && val2 == 'a')
			return array[22];
		else if (val1 == 'a' && val2 == 'b')
			return array[24];
		else if (val1 == 'a' && val2 == 'c')
			return array[26];
		else if (val1 == 'b' && val2 == 'a')
			return array[28];
		else if (val1 == 'b' && val2 == 'b')
			return array[30];
		else if (val1 == 'b' && val2 == 'c')
			return array[32];
		else if (val1 == 'c' && val2 == 'a')
			return array[34];
		else if (val1 == 'c' && val2 == 'b')
			return array[36];
		else if (val1 == 'c' && val2 == 'c')
			return array[38];
	}
	else if (op == array[40]) // 텍스트 파일의 &(#,@ 가능) 연산자 규칙
	{
		if (val1 == 'a' && val2 == 'a')
			return array[42];
		else if (val1 == 'a' && val2 == 'b')
			return array[44];
		else if (val1 == 'a' && val2 == 'c')
			return array[46];
		else if (val1 == 'b' && val2 == 'a')
			return array[48];
		else if (val1 == 'b' && val2 == 'b')
			return array[50];
		else if (val1 == 'b' && val2 == 'c')
			return array[52];
		else if (val1 == 'c' && val2 == 'a')
			return array[54];
		else if (val1 == 'c' && val2 == 'b')
			return array[56];
		else if (val1 == 'c' && val2 == 'c')
			return array[58];
	}
	else
		exit(-1);
}

char calcpost(char* postresult) // postfix expression을 인자로 받아서 계산
{
	stack<char>temp;//계산을 위한 stack

	char num1;
	char num2;

	int i = 0;
	while (postresult[i] != '\0')
	{
		if (postresult[i] == 'a' || postresult[i] == 'b' || postresult[i] == 'c') // 문자일 때 stack에 저장
			temp.push(postresult[i]);
		else if (postresult[i] == '@' || postresult[i] == '#' || postresult[i] == '&') //연산자일 때 꺼내서 계산
		{
			num2 = temp.top();
			temp.pop();
			num1 = temp.top();
			temp.pop();

			temp.push(txtrule(num1, postresult[i], num2));
		}
		i++;
	}
	return temp.top();   //최종 연산된 값
}

bool check1(char* str) // '(' 체크
{
	stack<char>pare; //  괄호를 저장하는 stack
	stack<char>trash; // 닫는 괄호가 먼저 들어오면 저장할 stack
	int i = 0;
	int temp1 = 0;// '(' 개수
	int temp2 = 0;// ')' 개수


	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			pare.push('(');
			temp1++;
		}
		else if (str[i] == ')' && temp1 > temp2)   // 정상 괄호
		{
			pare.pop();
			temp2++;
		}
		else if (str[i] == ')')    //')'가 먼저 들어오면 따로 처리
		{
			trash.push(')');
			temp2++;
		}
		i++;
	}

	if (!pare.empty())      //'('가 남아있는 경우(올바른 식x)
		return false;
	
	if (!trash.empty())    //')'가 더 많은 경우(올바른 식x)
		return false;
	
	else
		return true;


}
bool check2(char* str) // '[' 체크
{
	stack<char>pare;
	stack<char>trash;
	int i = 0;
	int temp1 = 0;
	int temp2 = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] == '[')
		{
			pare.push('[');
			temp1++;
		}
		else if (str[i] == ']' && temp1 > temp2)
		{
			pare.pop();
			temp2++;
		}
		else if (str[i] == ']')
		{
			trash.push(']');
			temp2++;
		}
		i++;
	}

	if (!pare.empty())
		return false;
	
	if (!trash.empty())
		return false;
	
	else
		return true;
}

bool check3(char* str) // '{' 체크
{
	stack<char>pare;
	stack<char>trash;
	int i = 0;
	int temp1 = 0;
	int temp2 = 0;
		
	while (str[i] != '\0')
	{
		if (str[i] == '{')
		{
			pare.push('{');
			temp1++;
		}
		else if (str[i] == '}' && temp1 > temp2)
		{
			pare.pop();
			temp2++;
		}
		else if (str[i] == '}')
		{
			trash.push('}');
			temp2++;
		}
		i++;
	}

	if (!pare.empty())
		return false;
	
	if (!trash.empty())
		return false;

	else
		return true;
}

bool check4(char* str) // a,b,c 가 두개 동시에 입력된 수식 판단(익명게시판에서 괄호치기만 판단하는 것을 늦게 봤습니다..)
{
	int i = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] == 'a' || str[i] == 'b' || str[i] == 'c')
		{
			if (str[i + 1] == 'a' || str[i + 1] == 'b' || str[i + 1] == 'c' || str[i + 1] == '(' || str[i + 1] == '{' || str[i + 1] == '[')
				return false;
		}
		i++;
	}
}

bool check5(char* str) // 닫는 괄호 뒤에 문자가 바로 나오는 경우 체크
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			if (str[i + 1] == 'a' || str[i + 1] == 'b' || str[i + 1] == 'c' || str[i + 1] == '(' || str[i + 1] == '{' || str[i + 1] == '[')
				return false;
		}
		i++;
	}
}

char* infixTopostfix(char* str) // infix 식을 postfix 식으로 바꿔주는 함수 
{
	stack<char> temp; // 계산을 위한 stack
	static char postarray[SIZE]; // postfix식을 저장하는 배열
	int i = 0;
	int	j = 0;
		
	while (str[i] != '\0')
	{
		switch (str[i])
		{
			case '(': // 열리는 괄호면 stack에 그냥 저장
				temp.push(str[i]);
				break;

			case '[':
				temp.push(str[i]);
				break;

			case '{':
				temp.push(str[i]);
				break;
			
			case ')':
				while(temp.top() != '(') // 닫히는 괄호가 나오면 스택에서 빼서 출력스택에 저장
				{
					postarray[j] = temp.top();
					j++;
					temp.pop();
				}
			
				if (temp.top() == '(')
					temp.pop();
				break;

			case ']':
				while (temp.top() != '[')
				{
					postarray[j] = temp.top();
					j++;
					temp.pop();
				}
				if (temp.top() == '[')
					temp.pop();
				break;

			case '}':
				while (temp.top() != '{')
				{
					postarray[j] = temp.top();
					j++;
					temp.pop();
				}
				if (temp.top() == '{')
					temp.pop();
				break;
			
			case 'a': //문자가 들어오면 배열에 저장
			case 'b':
			case 'c':
				postarray[j] = str[i];
				j++;
				break;

			case '@':  // 연산자 우선순위 계산해서 작동
			case '#':
			case '&':
				if (temp.empty())
					temp.push(str[i]);
			
				else
				{
					if (prio(str[i]) > prio(temp.top()))
					{
						temp.push(str[i]);
					}
					else if (prio(str[i]) <= prio(temp.top()))
					{
						postarray[j] = temp.top();
						j++;
						temp.pop();
						temp.push(str[i]);
					}

				}
				break;

			default: // 연산에 쓰이지 않는 문자가 들어왔을 때 처리
				checknum = checknum +1;
				break;
		}
		
		i++;
	}
	
	if (str[i] == '\0')  // 입력값이 끝나면 temp에 남아있는 연산자 꺼내기       
	{
		while (!temp.empty())
		{
			postarray[j] = temp.top();
			j++;
			temp.pop();
		}
		postarray[j] = '\0';
	}
	
	return postarray;
}

int prio(char str)
{
	double priority;
	switch (str)    // &연산자가 우선순위가 가장 높음
	{
		case '@':priority = 3;
			break;
		case '#':priority = 3;
			break;
		case '&':priority = 4;
			break;
		case '(':priority = 2;
			break;
		case '[':priority = 2;
			break;
		case '{':priority = 2;
			break;
		default: priority = 1;
			break;
	}
	return priority;
}
