#include <iostream>
#include"MyIntVector.h"
using namespace std;
void printVector(string name ,MyIntVector& v) {
	cout << endl;
	cout << "MyIntVector " << name << endl;
	cout << "capacity : " << v.capacity() << endl;
	cout << "size : " << v.size() << endl << endl;
}
void printElem(string name, MyIntVector& v) {
	cout << name <<"[0] : " << v[0] << endl;
	cout << name <<"[1] : " << v[1] << endl;
	cout << name << "[2] : " << v[2] << endl << endl;
}
void printElem2(string name, MyIntVector& v) {
	cout << name << "[3] : " << v[3] << endl;
	cout << name << "[4] : " << v[4] << endl;
	cout << name << "[5] : " << v[5] << endl << endl;
}

int main() {

	try {
		cout << "#########<<Test MyIntVector>>##########" << endl;
		cout << ">>Test Default constructor" << endl << endl;
		cout << "MyIntVector v1;" << endl;
		MyIntVector v1;

		printVector("v1", v1);
		cout << "MyIntVector v2(50);" << endl;
		MyIntVector v2(50);
		printVector("v2", v2);
	

		cout << "----------------------" << endl;
		cout << ">>push back(1),(2),(3) into v2" << endl << endl;
		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(3);
		printVector("v2", v2);

		printElem("v2", v2);
		cout << "----------------------" << endl;
		cout << ">>Test Copy constructor" << endl << endl;
		cout << "MyIntVector v6 = v2" << endl;
		MyIntVector v6 = v2;
		printVector("v6", v6);
		printElem("v6", v6);
		cout << "----------------------" << endl;

		cout << ">>Test = Operator" << endl << endl;
		cout << "v1 = v2" << endl;
		v1 = v2;

		printVector("v1", v1);
		printElem("v1", v1);
		cout << "----------------------" << endl;
		cout << ">>Test += Operator" << endl << endl;
		cout << "v1 += v2" << endl;
		v1 += v2;
		printVector("v1", v1);
		printElem("v1", v1);
		printElem2("v1", v1);
		//cout << "v1[6] : " << v1[6] << endl;
		cout << "----------------------" << endl;
		cout << ">>Pop back v1 x 3" << endl << endl;
		
		v1.pop_back();
		v1.pop_back();
		v1.pop_back();
		printVector("v1", v1);
		cout << "----------------------" << endl;
		cout << ">>Test + Operator" << endl << endl;
		MyIntVector v3;
		cout << "v3 = v1 + v2" << endl;
		v3 = v1 + v2;
		printElem("v1", v1);
		printElem("v2", v2);
		printVector("v3", v3);
		printElem("v3", v3);
		cout << "----------------------" << endl;
		cout << ">>Test - Operator" << endl << endl;
		MyIntVector v4(50);
		cout << "v4 = v1 - v2" << endl;
		v4 = v1-v2;
		printElem("v1", v1);
		printElem("v2", v2);
		printVector("v4", v4);
		printElem("v4", v4);
		cout << "----------------------" << endl;
		cout << ">>Test * Operator" << endl << endl;
		int Dot_result;
		cout << "Dot_result = v3 * v1" << endl;
		cout << "Dot_result : " << v3 * v1 << endl;
		cout << "----------------------" << endl;
		cout << ">>Test - Operator(Unary)" << endl << endl;
		MyIntVector v5;
		cout << "v5 = -v1" << endl;
		v5 = -v1;
		printVector("v5", v5);
		printElem("v5", v5);
		cout << "----------------------" << endl;
		cout << ">>Test == Operator" << endl << endl;
		printElem("v1", v1);
		printElem("v2", v2);
		printElem("v3", v3);
		cout << "v1 == v2 result: " << (v1==v2) << endl;
		cout << "v3 == v1 result: " << (v3 == v1) << endl;
		cout << "----------------------" << endl;
		cout << ">>Test () Operator(Unary)" << endl << endl;
		cout << "v1(5)" << endl;
		v1(5);
		printElem("v1", v1);
		cout << "----------------------" << endl;
		cout << ">>Test reserve(size_t n)" << endl << endl;
		cout << "v1.reserve(2)" << endl;
		v1.reserve(2);
		printVector("v1", v1);
		cout << "v1.reserve(20)" << endl;
		v1.reserve(20);
		printVector("v1", v1);
		cout << ">>Test bool is_empty & void clear" << endl << endl;
		cout << "v1.is_empty() : " << v1.is_empty() << endl;
		cout << "v1.clear()" <<  endl;
		v1.clear();
		cout << "v1.is_empty() : " << v1.is_empty() << endl;

		cout << "----------------------" << endl;
		cout << "Test error message" << endl << endl;
		cout << "print v1[1]" << endl;
		cout << v1[1] << endl;
		

	}


	catch(out_of_range& e){
		cout << "Error : " << e.what() << endl;
	}
	catch (length_error& e) {
		cout << "Error : " << e.what() << endl;
	}
	return 0;
}