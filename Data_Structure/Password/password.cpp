#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(void)
{
    string wordlen;
    string txt;

    getline(cin, wordlen); // 단어길이 입력
    int n = stoi(wordlen);

    getline(cin, txt); // input 텍스트 입력
    string input = txt;

    unordered_map<string, int> wordsave; // 저장할 자료구조        

    int length = input.length();
    string password = "";

    
    for (int i = 0; i < input.length() - n + 1; i++) 
    {
        password.assign(input, i, n); // n만큼 짤라서 저장
        wordsave[password] = wordsave[password]+ 1; // 초기값은 0, 단어의 반복 횟수 저장
    }

    int max = 0;
    string output;

    unordered_map<string, int>::iterator itr; // 이터레이터 선언
    for (itr = wordsave.begin(); itr != wordsave.end(); itr++) //맵전체 탐색
    {
        if (max < itr->second) // 저장횟수가 가장 높은 비밀번호 output에 저장
        {
            max = itr->second;
            output = itr->first;
        }
    }
    
    cout << "Output = " << output <<  endl;
 }