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

void fileRead(ifstream& fin, vector<string>& v) //������ �д� �Լ�
{
    string line;

    while (getline(fin, line))
        v.push_back(line);
}


void search(vector<string>& v, string& word) //�ܾ ã�� �Լ�
{
    for (int i = 0; i < v.size(); i++) {
        int index = v[i].find(word);
        if (index != -1) {
           a = a + 1;
        }
    }

}

int main(int argc, char* argv[]) //���Ͽ��� �ܾ ã�� ������ ���(�Է¹޾Ƽ� �����ϸ� �����߻�)
{
    vector<string> v;
    ifstream fin("text.txt");
    if (!fin) {
        cout << "���� �Է�����";
        return 0;
    }

    fileRead(fin, v);
    string word;
    cout << "�˻��� �ܾ �Է��� �ּ��� : ";
    cin >> word;
    search(v, word);
    cout << "�ܾ��� Ƚ����:" << a << "�� �Դϴ�" << endl;
}

