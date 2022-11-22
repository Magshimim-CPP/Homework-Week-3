#include "Vector.h"

using namespace std;

//setting defined constant variables
#define ZERO 0
#define ERROR -9999
#define ONE 1
#define TWO 2

/*
Constructor function for a Vector object.
Input: int n (for the capacity and resizeFactor)
Output: none
*/
Vector::Vector(int n)
{
	//if n is smaller then 2, n equals 2. (requirement)
	if (n < TWO)
	{
		n = TWO;
	}
	//setting object filds to defult values.
	_capacity = n;
	_elements = new int[_capacity];
	_size = ZERO;
	_resizeFactor = n;
}

/*
Copy constructor function for a Vector object.
Input: const Vector& other (the vactor object to copy)
Output: none
*/
Vector::Vector(const Vector& other)
{
	//copying the values from the other vector's filds to this vector.
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;

	//creating a dynamic array for this vector's elements.
	this->_elements = new int[this->_capacity];

	//copying the elements from the other vector's array to this vector.
	for (int i = ZERO; i < this->_capacity; i++)
	{
		this->_elements[i] = other._elements[i];
	}
}

/*
OverLoading for the '=' operator, to copy all of the values from the vector 'other' to the given vector.
Input: the vector we use it on (this), and the vector we copy (other).
Output: returning the result vector (this vector).
*/
Vector& Vector::operator=(const Vector& other)
{
	//(if we are comparing a vector to itself)
	if (this == &other)
	{
		return *this;
	}

	//deleting this vector's elements array in case he hlready had one befor copying.
	delete[] this->_elements;

	//copying the values from the other vector's filds to this vector.
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;
	
	//creating a new empty elements array for this vector
	this->_elements = new int[this->_capacity];

	//copying the elements from the other vector's array to this vector.
	for (int i = ZERO; i < this->_capacity; i++)
	{
		this->_elements[i] = other._elements[i];
	}

	//returning the result vector.
	return *this;
}

/*
OverLoading for the '[]' operator, to return the element in the n'th place from the vector's array (or the first element if n is out of range).
Input: int n
Output: the element in the n'th place from the vector's array (or the first element if n is out of range) (this->_elements[n]).
*/
int& Vector::operator[](int n) const
{
	//if 'n' is in the vector's size boundaries, returning the n'th element of the vector's array.
	if (n < this->_size && n >= ZERO)
	{
		return this->_elements[n];
	}
	//if 'n' was out of the size range, printing an error message and returning the first element of the vector's array.
	else
	{
		cout << "ERROR: n was out of the vector's boundarys\nReturning the first element\n" << endl;
		return this->_elements[ZERO];
	}
}

/*
Destructor function for a Vector object.
Input: none
Output: none
*/
Vector::~Vector()
{
	//deleting the elements dynamic array.
	delete[] _elements;
}

/*
Const 'get' function that returns the vector's size.
Input: none
Output: the vector's size (int _size).
*/
int Vector::size() const
{
	return _size;
}

/*
Const 'get' function that returns the vector's capacity.
Input: none
Output: the vector's capacity (int _capacity).
*/
int Vector::capacity() const 
{
	return _capacity;
}

/*
Const 'get' function that returns true if the vector is empty or false if it's not.
Input: none
Output: true if the vector is empty or false if it's not (bool _size <= ZERO).
*/
bool Vector::empty() const
{
	return _size <= ZERO;
}

/*
Const 'get' function that returns the vector's resize factor.
Input: none
Output: the vector's resize factor (int _resizeFactor).
*/
int Vector::resizeFactor() const
{
	return _resizeFactor;
}

/*
Function removes and returns the last element of the vector.
Input: none
Output: the last element of the vector (int element).
*/
int Vector::pop_back()
{
	int element = ZERO;

	//checking if the vector is empty (returning error if it is).
	if (_size == ZERO)
	{
		cout << "ERROR: pop from empty vector\n";
		return ERROR;
	}
	//setting 'element' variable to the last value in the _elements array.
	element = _elements[_size-ONE];
	//setting the last value in the _elements array to 0.
	_elements[_size-ONE] = ZERO;
	//reducing the size by 1 (the element we popped)
	_size--;
	//returning the popped element.
	return element;
}

/*
Function changes the vector's _size to n. if new elements are added this way, their value is 'val'.
Input: const int n, const int& val
Output: none.
*/
void Vector::resize(const int n, const int& val)
{
	//resizing the vector.
	resize(n);
	//adding val to all of the elements between size to n.
	AddValUntilN(val, n);
}

/*
Function assigns the given value to all of the elemnts in the vector's array.
Input: const int val
Output: none
*/
void Vector::assign(const int val)
{
	//looping through all the elements in the array and setting their value to val.
	for (int i = ZERO; i < _capacity; i++)
	{
		_elements[i] = val;
	}
	//changing size to capacity (full).
	_size = _capacity;
}

/*
Function assigns the given value to all of the elemnts in the vector's array.
Input: const int val
Output: none
*/
void Vector::AddValUntilN(const int val, const int n)
{
	//looping through the elements between the current size to n, and setting their value to val.
	for (int i = (_size); i < n; i++)
	{
		_elements[i] = val;
	}
	//changing size to n.
	_size = n;
}

/*
Function changes _size to n, unless n is greater than the vector's capacity
Input: const int n
Output: none
*/
void Vector::resize(const int n)
{
	//if n is larger then the current capacity, using reserve(n) to make the capacity bigger then n.
	if (n > _capacity)
	{
		reserve(n);
	}
	//if n is smaller or equal to the capacity, setting size to n.
	else
	{
		_size = n;
	}
}

/*
Function changes the vector's capacity to be bigger then n.
Input: const int n
Output: none.
*/
void Vector::reserve(const int n)
{
	//setting a temp elements pointer to take '_elements' address.
	int* tempElements = _elements;

	//as long as n is bigger then the current capacity, adding the resizeFactor to capacity.
	while (_capacity < n)
	{
		_capacity += _resizeFactor;
	}
	//creating a new dynamic array for '_elements' with the new capacity.
	_elements = new int[_capacity];

	//looping until '_size' to copy all of the previous elements back to the array (from tempElements to _elements).
	for (int i = ZERO; i < _size; i++)
	{
		_elements[i] = tempElements[i];
	}

	//deleting tempElements.
	tempElements = nullptr; //(safety)
	delete[] tempElements;
}

/*
Function adds an element at the end of the vector.
Input: const int& val (value of the element to add)
Output: none
*/
void Vector::push_back(const int& val)
{
	//entering condition if the vector is full.
	if (_size == _capacity)
	{
		//resizing the vector (adding resize factor to the capacity).
		resize(_size + ONE); //(size + 1 because the condition in resize is '_capacity < n')
	}
	//setting the current element to the given value.
	_elements[_size] = val;
	//increasing size by 1 (the added element).
	_size++;
}