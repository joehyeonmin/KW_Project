//2016726072_������

#include <cstdlib>
#include <iostream>
#include <stack>
#include <cstring>
#include <stdio.h>
#include <fstream>

#define SIZE 1024

using namespace std;

bool check1(char* str); // ��ȣġ�� Ȯ��
bool check2(char* str);
bool check3(char* str);
bool check4(char* str); // ����ó��(�߰�)
bool check5(char* str);

char* infixTopostfix(char* str);//���Ƚ��� ����Ʈ�Ƚ��� �ٲ㼭 ����
int prio(char str);//�����ڿ� ��ȣ�� �켱����

char calcpost(char* postresult);//����Ʈ�Ƚ� ����ؼ� ���
char txtrule(char val1, char op, char val2);//���Ͽ��� ���� �޾ƿ���
int checknum = 0; //�ٸ� ���ڸ� �޾��� �� ó���ϴ� ����

int main(){

	char input[SIZE]; // �Է¹��� ������ �����ϴ� �迭
	char* postresult; // postfix���� �����ϴ� ������

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

char txtrule(char val1, char op, char val2) // �ؽ�Ʈ ���Ͽ� �ִ� ��Ģ�� �̿��Ͽ� ���
{
	char array[SIZE];
	int position = 0;
	size_t nread;

	ifstream fileopen; //�ؽ�Ʈ ������ �޾Ƽ� �迭�� ����
	fileopen.open("operations.txt");
	if (fileopen.is_open()) {
		while (!fileopen.eof() && position < SIZE) {
			fileopen.get(array[position]);
			position++;
		}
		array[position - 1] = '\0';
	}

	if (op == array[0]) // �ؽ�Ʈ ������ @(#,& ����) ������ ��Ģ
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
	else if (op == array[20]) // �ؽ�Ʈ ������ #(@,& ����) ������ ��Ģ
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
	else if (op == array[40]) // �ؽ�Ʈ ������ &(#,@ ����) ������ ��Ģ
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

char calcpost(char* postresult) // postfix expression�� ���ڷ� �޾Ƽ� ���
{
	stack<char>temp;//����� ���� stack

	char num1;
	char num2;

	int i = 0;
	while (postresult[i] != '\0')
	{
		if (postresult[i] == 'a' || postresult[i] == 'b' || postresult[i] == 'c') // ������ �� stack�� ����
			temp.push(postresult[i]);
		else if (postresult[i] == '@' || postresult[i] == '#' || postresult[i] == '&') //�������� �� ������ ���
		{
			num2 = temp.top();
			temp.pop();
			num1 = temp.top();
			temp.pop();

			temp.push(txtrule(num1, postresult[i], num2));
		}
		i++;
	}
	return temp.top();   //���� ����� ��
}

bool check1(char* str) // '(' üũ
{
	stack<char>pare; //  ��ȣ�� �����ϴ� stack
	stack<char>trash; // �ݴ� ��ȣ�� ���� ������ ������ stack
	int i = 0;
	int temp1 = 0;// '(' ����
	int temp2 = 0;// ')' ����


	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			pare.push('(');
			temp1++;
		}
		else if (str[i] == ')' && temp1 > temp2)   // ���� ��ȣ
		{
			pare.pop();
			temp2++;
		}
		else if (str[i] == ')')    //')'�� ���� ������ ���� ó��
		{
			trash.push(')');
			temp2++;
		}
		i++;
	}

	if (!pare.empty())      //'('�� �����ִ� ���(�ùٸ� ��x)
		return false;
	
	if (!trash.empty())    //')'�� �� ���� ���(�ùٸ� ��x)
		return false;
	
	else
		return true;


}
bool check2(char* str) // '[' üũ
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

bool check3(char* str) // '{' üũ
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

bool check4(char* str) // a,b,c �� �ΰ� ���ÿ� �Էµ� ���� �Ǵ�(�͸�Խ��ǿ��� ��ȣġ�⸸ �Ǵ��ϴ� ���� �ʰ� �ý��ϴ�..)
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

bool check5(char* str) // �ݴ� ��ȣ �ڿ� ���ڰ� �ٷ� ������ ��� üũ
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

char* infixTopostfix(char* str) // infix ���� postfix ������ �ٲ��ִ� �Լ� 
{
	stack<char> temp; // ����� ���� stack
	static char postarray[SIZE]; // postfix���� �����ϴ� �迭
	int i = 0;
	int	j = 0;
		
	while (str[i] != '\0')
	{
		switch (str[i])
		{
			case '(': // ������ ��ȣ�� stack�� �׳� ����
				temp.push(str[i]);
				break;

			case '[':
				temp.push(str[i]);
				break;

			case '{':
				temp.push(str[i]);
				break;
			
			case ')':
				while(temp.top() != '(') // ������ ��ȣ�� ������ ���ÿ��� ���� ��½��ÿ� ����
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
			
			case 'a': //���ڰ� ������ �迭�� ����
			case 'b':
			case 'c':
				postarray[j] = str[i];
				j++;
				break;

			case '@':  // ������ �켱���� ����ؼ� �۵�
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

			default: // ���꿡 ������ �ʴ� ���ڰ� ������ �� ó��
				checknum = checknum +1;
				break;
		}
		
		i++;
	}
	
	if (str[i] == '\0')  // �Է°��� ������ temp�� �����ִ� ������ ������       
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
	switch (str)    // &�����ڰ� �켱������ ���� ����
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
