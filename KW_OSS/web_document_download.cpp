#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <urlmon.h>
#include <fcntl.h>
#include <urlmon.h>
#include <Windows.h>
#include <WinInet.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <UrlMon.h>
#pragma comment(lib,"UrlMon.lib")

#define SIZE 100

using namespace std;

std::wstring s2ws(const std::string& s) // string을 LPCWSTR타입으로 변경하는 함수
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


int main(int argc, char* argv[])
{

	fstream fs;
	fs.open("text.txt");
	string url = argv[0];

	std::wstring stemp = s2ws(url);
	LPCWSTR result = stemp.c_str();


	URLDownloadToFile(0, L"http://www.gutenberg.org/files/1342/1342-0.txt", L"text.txt", 0, 0);
	//url을 사용자에게 입력받아서 실행하면 파일이 깨짐

	int ch;
	FILE* p_src_file = NULL, * p_dest_file = NULL;
	if (fopen_s(&p_src_file, "text.txt", "rt") == 0) {// 대문자로 변환해서 파일 저장
		if (fopen_s(&p_dest_file, "text1.txt", "wt") == 0) {
			while ((ch = fgetc(p_src_file)) != EOF) {
				if (ch >= 'a' && ch <= 'z')
					ch -= 32;
				fputc(ch, p_dest_file);
			}
			fclose(p_dest_file);
		}
		fclose(p_src_file);
	}
	return 0;
}
	


