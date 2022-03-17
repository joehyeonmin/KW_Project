//2016726072 ������

#include "MyIntVector.h"
#include <cstdlib>
#include <iostream>

using namespace std;

MyIntVector::MyIntVector(size_t init_capacity) { //default constructors
	data = new int[init_capacity];
	c = init_capacity;
	s = 0;
}


MyIntVector::MyIntVector(const MyIntVector& source) { //copy constructors
	data = new int[source.c];
	c = source.c;
	s = source.s;
	copy(source.data, source.data + source.s, data);
}

MyIntVector::~MyIntVector() { //destructor
	delete[] data;
}


MyIntVector& MyIntVector::operator=(const MyIntVector& source) { //assignment operator
	if (this == &source)
		return *this;
	if (c != source.c)
	{
		delete[] data;
		data = new int[source.c];
		c = source.c;
	}
	s = source.s;
	copy(source.data, source.data + s, data);
	return *this;
}

void MyIntVector::operator+=(const MyIntVector& source) {
	if (source.is_empty()) 
		return; // is_empty()�Լ� ���
	while (this->s + source.s > this->c)
		this->reserve(this->c * 2); // reserve �Լ� ���
	
	copy(source.data, source.data + source.s, this->data + this->s);
	s += source.s;
}

int& MyIntVector::operator[](int x) {
	if (x >= this->s || x < 0) { 
		cout << "������ ������ϴ�." << endl;
		exit(-1);
	}
	return data[x];
}

MyIntVector MyIntVector::operator+(const MyIntVector& source) {
	if (this->s != source.s) { 
		cout << "ũ�Ⱑ �ٸ��ϴ�." << endl;
		return -1;
	}
	MyIntVector temp(*this);

	for (int i = 0; i < temp.s; i++)
		temp.data[i] = temp.data[i] + source.data[i];

	return temp;
}

MyIntVector MyIntVector::operator-(const MyIntVector& source) {
	if (this->s != source.s) { 
		cout << "ũ�Ⱑ �ٸ��ϴ�." << endl;
		return -1;
	}
	MyIntVector temp(*this);
	for (int i = 0; i < temp.s; i++)
		temp.data[i] = temp.data[i] - source.data[i];

	return temp;
}

double MyIntVector::operator*(const MyIntVector& source) {
	if (this->s != source.s) { 
		cout << "ũ�Ⱑ �ٸ��ϴ�." << endl;
		return -1;
	}
	MyIntVector temp(*this);
	int sum = 0;
	for (int i = 0; i < temp.s; i++) {
		temp.data[i] = temp.data[i] * source.data[i];
		sum = sum + temp.data[i];
	}
	return sum;
}

MyIntVector MyIntVector::operator-() {
	MyIntVector temp(*this);
	for (int i = 0; i < temp.s; i++)
		temp.data[i] = temp.data[i] * -1;
	return temp;
}

bool MyIntVector::operator==(const MyIntVector& source) {
	if (this->s != source.s)
		return false;
	else
	{
		for (int i = 0; i < this->s; i++)
			if (this->data[i] != source.data[i])
				return false;
		return true;
	}
}

MyIntVector& MyIntVector::operator()(int x) {
	for (int i = 0; i < this->s; i++) 
		this->data[i] = x;
	return *this;
}

void MyIntVector::pop_back() {
	if (this->is_empty()) 
		return; // is_empty()�Լ� ���
	this->s--;
}

void MyIntVector::push_back(int x) {
	if (this->s == this->c) 
		this->reserve(2 * c); // reserve()�Լ� ���
	data[this->s] = x;
	this->s++;
}

void MyIntVector::reserve(size_t n) {
	if (n < this->s) 
		return; 
	int* temp = new int[n];
	copy(data, data + this->s, temp);
	delete[] data;
	data = temp;
	this->c = n;
}

bool MyIntVector::is_empty() const {
	if (s == 0)
		return true;
	else
		return false;
}

void MyIntVector::clear() {
	this->s = 0;
}


