#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <string> 
#include <queue>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define BUFFER_SIZE 6

using namespace std;

struct Node {
	char symbol;
	int frequency;
	Node* left;
	Node* right;
};

struct cmp {
	bool operator()(Node* A, Node* B)
	{
		return A->frequency > B->frequency;
	}
};

class HuffmanTree {
public:
	~HuffmanTree() {
		FirtstTree(root);
		root = nullptr;
		ummap1.clear();
		ummap2.clear();
		while (!pq.empty())
			pq.pop();
	}

public:
	const unordered_map<char, string>& Getummap2()
	{
		return ummap2;
	}

public:
	void Create(const string& str)
	{
		for (const auto iter : str)
			++ummap1[iter];
		for (const auto iter : ummap1)
		{
			Node* newNode = new Node;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->symbol = iter.first;
			newNode->frequency = iter.second;
			pq.push(newNode);
		}

		MakeTree();
		string tmp = "";
		FindTree(root, tmp);
	}

private:
	void MakeTree() {

		int temp = pq.size() - 1;
		for (int i = 0; i < temp; ++i)
		{
			Node* newNode = new Node;
			newNode->symbol = 0;
			newNode->right = pq.top();
			pq.pop();
			newNode->left = pq.top();
			pq.pop();
			newNode->frequency = newNode->right->frequency + newNode->left->frequency;
			pq.push(newNode);
		}
		root = pq.top();
	}

	void FindTree(Node* p, string str)
	{
		if (p == nullptr)
			return;
		FindTree(p->left, str + '0');
		FindTree(p->right, str + '1');
		if (p->symbol != 0)
		{
			ummap2[p->symbol] = str;
		}
	}
	void FirtstTree(Node* p)
	{
		if (p == nullptr)
			return;
		FirtstTree(p->left);
		FirtstTree(p->right);
		delete p;
		p = nullptr;
	}

private:
	Node* root = nullptr;
	unordered_map<char, int> ummap1;
	unordered_map<char, string> ummap2;
	priority_queue<Node*, vector<Node*>, cmp> pq;
};

int main() {

	HuffmanTree t;

	ofstream writeFile1("new9.hfb", ios_base::out | ios_base::trunc | ios_base::binary);
	ofstream writeFile2("new10.hft");

	ifstream readFile;
	readFile.open("5.txt");

	string str;

	if (readFile.is_open())
	{ 
		getline(readFile, str);
		t.Create(str);
	}

	unordered_map<char, string> ummap2 = t.Getummap2();
	cout << "압축할 문자열 : " << str << "\n\n";
	
	writeFile2 << "encoding table" << endl;
	cout << "\n인코딩 정보: \n";
	for (const auto iter : ummap2)
	{
		cout << iter.first << ": " << iter.second << "\n";
		writeFile2 << iter.first << ": " << iter.second << endl;
		//writeFile1 << iter.first << ": " << iter.second << " ";
	}


	cout << "\n\n압축된 정보: ";
	writeFile2 << "encoded text" << endl;
	string str2 = "";
	
	for (auto iter : str) {
		cout << ummap2[iter] << ' ';
		str2 = str2 + ummap2[iter];
		writeFile2 << ummap2[iter] << ' ';
	}

	
	while (str2.length() % 8) 
		str2 += "0";
	
	for (int i = 0; i < str2.length(); i += 8) {
		char c = static_cast<char>(stoi(str2.substr(i, 8), nullptr, 2));
		writeFile1 << c;
	}
	
	
}


