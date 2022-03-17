#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>>
#include <cstdio>
#include <stdlib.h>
#include <urlmon.h>
#include <fcntl.h>
#include <urlmon.h>
#include <Windows.h>
#include <WinInet.h>
#include <direct.h>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;
int a = 0;

void fileRead(ifstream& fin, vector<string>& v) //파일을 읽는 함수
{
    string line;

    while (getline(fin, line))
        v.push_back(line);
}


void search(vector<string>& v, string& word) //단어를 찾는 함수
{
    for (int i = 0; i < v.size(); i++) {
        int index = v[i].find(word);
        if (index != -1) {
           a = a + 1;
        }
    }

}

int main(int argc, char* argv[]) //파일에서 단어를 찾아 개수를 출력(입력받아서 실행하면 오류발생)
{
    vector<string> v;
    ifstream fin("text.txt");
    if (!fin) {
        cout << "에러 입력파일";
        return 0;
    }

    fileRead(fin, v);
    string word;
    cout << "검색할 단어를 입력해 주세요 : ";
    cin >> word;
    search(v, word);
    cout << "단어의 횟수는:" << a << "개 입니다" << endl;
}

