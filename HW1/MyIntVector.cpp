#include "MyIntVector.h"

MyIntVector::MyIntVector(size_t init_capacity)
{
	data = new int[init_capacity];
	v_capacity = init_capacity;
	v_used = 0;
}

MyIntVector::MyIntVector(const MyIntVector& v)
{
	data = new int[v.v_capacity];
	v_capacity = v.v_capacity;
	v_used = v.v_used;
	std::copy(v.data, v.data + v_used, data);
}

MyIntVector::~MyIntVector()
{
	delete[] data;
}

MyIntVector& MyIntVector::operator=(const MyIntVector& v)
{
	if (this == &v) return *this;
	if (v_capacity != v.v_capacity)
	{
		delete[] data;
		data = new int[v.v_capacity];
		v_capacity = v.v_capacity;
	}
	v_used = v.v_used;
	std::copy(v.data, v.data + v_used, data);
	return *this;
}

void MyIntVector::operator+=(const MyIntVector& v)
{
	if (v_capacity < v_used + v.v_used)
		reserve(v_used + v.v_used);
	std::copy(v.data, v.data + v.v_used, data + v_used);
	v_used += v.v_used;
}

int& MyIntVector::operator[](size_t index)
{
	if (!(index >= 0 && index < v_used))
		throw std::out_of_range("input index is out of range");

	return data[index];
}

MyIntVector MyIntVector::operator+(const MyIntVector& v)
{
	if (v_used != v.v_used)
		throw std::length_error("vector sizes is not same");

	MyIntVector temp(*this);
	temp.reserve(v_used);
	for (int i = 0; i < v_used; i++)
		temp.data[i] += v.data[i];
	return temp;
}

MyIntVector MyIntVector::operator-(const MyIntVector& v)
{
	if (v_used != v.v_used)
		throw std::length_error("vector sizes is not same");
	MyIntVector temp(*this);
	temp.reserve(v_used);
	for (int i = 0; i < v_used; i++)
		temp.data[i] -= v.data[i];

	return temp;
}

int MyIntVector::operator*(const MyIntVector& v)
{
	if (v_used != v.v_used)
		throw std::length_error("vector sizes is not same");

	int DOT = NULL;

	for (int i = 0; i < v_used; i++)
		DOT += this->data[i] * v.data[i];

	return DOT;
}

MyIntVector MyIntVector::operator-()
{
	MyIntVector temp(*this);
	temp.reserve(v_used);
	for (int i = 0; i < v_used; i++)
		temp.data[i] *= -1;

	return temp;
}

bool MyIntVector::operator==(const MyIntVector& v)
{
	if(v_used != v.v_used)
		throw std::length_error("vector sizes is not same");
	for (int i = 0; i < v_used; i++)
		if (this->data[i] != v.data[i]) 
			return false;
	return true;
}

void MyIntVector::operator()(int x)
{
	for (int i = 0; i < v_used; i++)
		this->data[i] = x;
}

void MyIntVector::pop_back()
{
	if(!(v_used > 0))
		throw std::out_of_range("nothing to pop back in this vector");

	data[--v_used] = NULL;
}

void MyIntVector::push_back(int x)
{
	if (v_used == v_capacity)
		reserve(v_capacity * 2);

	data[v_used++] = x;
}

size_t MyIntVector::capacity() const
{
	return v_capacity;
}

size_t MyIntVector::size() const
{
	return v_used;
}

void MyIntVector::reserve(size_t n)
{
	int* temp;
	if (n <= v_used) 
		n = v_used;

	temp = new int[n];
	std::copy(data, data + v_used, temp);
	delete[] data;
	data = temp;
	v_capacity = n;
}

bool MyIntVector::is_empty() const
{
	if (v_used == 0) 
		return true;
	else 
		return false;
}

void MyIntVector::clear()
{
	delete[] data;
	data = NULL;
	v_used = 0;
	v_capacity = 0;
}


