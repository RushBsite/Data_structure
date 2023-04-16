#pragma once
#include <stdexcept>
#include <algorithm>

class MyIntVector {
public:
	MyIntVector(size_t init_capacity = Default_Capacity); //default constructor
	//precondition: init_capacity(integer) should be more than 0 
	//postcondition: init_capacity - > v_capacity, if init_capacity N/A.. Default_Capacity -> v_capacity
	//set the size of array (data), allocate into HEAP, initialize v_used = 0; v_capacity= ..

	MyIntVector(const MyIntVector& v); //Copy constructor for deep copy
	//precondition: target Vector should be different with original Vector (copy v1 to v2,  not in v1)
	//postcondition: make same structure with v(copy of v)
	//v1 data(original) - > v2 data (target) , initialize with same value

	~MyIntVector(); //Destructor
	//preconditon: None
	//postcondition: delete vector data & return HEAP data resource 

	MyIntVector& operator=(const MyIntVector& v); //Assignment operator (=) for deep copy
	//precnd: obj should be MyIntVector Type
	//postcnd: Original vector's data turn into target vector's data.
	// v1 = v1 should return v1
	
	void operator+=(const MyIntVector& v); //Operator: += : Appends RHS object to LHS one
	//precnd: obj should be MyIntVector Type
	//postcnd: put target vector(v2) into original vector(v1)'s back
	//capacity of new v1 is 'v_used of v1 + v_used of v2' if v_capcity is smaller than that
	int& operator[](size_t index); // Operator[] : 
	//precnd: index should be in '0<= index < v_used'
	//postcnd: return reference of data with index
	//If the requested position is out of range, Print some messages(error) and terminate the program.

	MyIntVector operator+(const MyIntVector& v); //Binary operator +
	//precnd:obj should be MyIntVector Type, applicable only when the sizes of the two operands is the same
	//postcnd: add data in each vector index by index
	//Returns an object that is a vector-sum of the two operand objects.
	MyIntVector operator-(const MyIntVector& v); //Binary operator -
	//precnd: obj should be MyIntVector Type, applicable only when the sizes of the two operands is the same
	//postcnd: subtract data in each vector index by index
	//Returns an object that is a vector-difference of the two operand objects.

	int operator*(const MyIntVector& v); //Binary operator * 
	//precnd: obj should be MyIntVector Type, applicable only when the sizes of the two operands is the same
	//postcnd: multiply data in each vector index by index , make Dot product of vectors
	//Returns the scalar product (or dot product) value of the two operand objects.

	MyIntVector operator-(); //Unary operator -
	//precnd: None
	//postcnd: store every elements in negative ver. (new obj)
	//Returns an object of which each element is the unary negation of the corresponding element in the operand object.

	bool operator==(const MyIntVector& v); // Binary operator ==
	//precnd:  obj should be MyIntVector Type, size(v_used) of each vectors should be same
	//postcnd: compare each vectors data, index by index
	//Returns whether or not the two operand vectors are the same. 

	void operator()(int element); // Unary operator ()
	//precnd: factor should be integer
	//postcnd: every data in v_used be the value of element(input)
	//Makes every element of this object be the value of the integer-valued (int-typed) operand.

	void pop_back(); //pop back func
	//precnd: func should work when v_used is more than 0
	//postcnd: remove data at end of the vector(last used index)
	//Removes the last element in the vector, effectively reducing the vector size by one and invalidating all references to it.

	void push_back(int x); // puch back func
	//precnd: factor should be integer
	//postcnd: if v_capacity is full , double current capacity using reserve func
	//Adds a new element at the end of the vector, after its current last element. The content of this new element is initialized to a copy of x.

	size_t capacity() const; // capcity getter func
	//precnd: None
	//postcnd: Returns the size of the allocated storage space for the elements of the vector container.

	size_t size() const; // used size getter func
	//precnd: None
	//postcnd: Returns the number of elements in the vector container.


	void reserve(size_t n); // turn capacity into 'n'
	//precnd: n(integer) should be more than 0
	//postcnd: Requests that the capacity of the allocated storage space for the elements of the vector container be at least enough to hold n elements.
	// if n is lower(or same) than size(v_used) fix n into v_used, 

	bool is_empty() const; //Returns whether the vector container is empty, 
						   //i.e., whether or not its size is 0.
	//precnd: None 
	//postcnd: if v_used is 0 return true , v_used is not 0 return false

	void clear(); // All the elements of the vector are dropped: they are removed from the vector container,
				  //leaving the container with a size of 0 and a default capacity.
	//precnd: None
	//postcnd: delete currnet data, pointer at NULL, initialize v_used , v_capacity into 0
private:
	int *data;
	static const size_t Default_Capacity = 100; //디폴트 크기 : 100
	size_t v_capacity; //MyIntVector 크기 최대값(용량)
	size_t v_used; //MyIntVector 현재 크기(사용량)
};