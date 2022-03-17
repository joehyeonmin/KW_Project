#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(void)
{
    string wordlen;
    string txt;

    getline(cin, wordlen); // �ܾ���� �Է�
    int n = stoi(wordlen);

    getline(cin, txt); // input �ؽ�Ʈ �Է�
    string input = txt;

    unordered_map<string, int> wordsave; // ������ �ڷᱸ��        

    int length = input.length();
    string password = "";

    
    for (int i = 0; i < input.length() - n + 1; i++) 
    {
        password.assign(input, i, n); // n��ŭ ©�� ����
        wordsave[password] = wordsave[password]+ 1; // �ʱⰪ�� 0, �ܾ��� �ݺ� Ƚ�� ����
    }

    int max = 0;
    string output;

    unordered_map<string, int>::iterator itr; // ���ͷ����� ����
    for (itr = wordsave.begin(); itr != wordsave.end(); itr++) //����ü Ž��
    {
        if (max < itr->second) // ����Ƚ���� ���� ���� ��й�ȣ output�� ����
        {
            max = itr->second;
            output = itr->first;
        }
    }
    
    cout << "Output = " << output <<  endl;
 }