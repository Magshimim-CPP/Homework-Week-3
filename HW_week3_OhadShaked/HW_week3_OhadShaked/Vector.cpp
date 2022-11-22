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
	if (n < TWO)
	{
		n = TWO;
	}
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
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;

	this->_elements = new int[this->_capacity];

	for (int i = ZERO; i < this->_capacity; i++)
	{
		this->_elements[i] = other._elements[i];
	}
}

/*
OverLoading for the '=' operator, to copy all of the values from the vector 'other' to the given vector.
Input: the vector we use it on (this), and the vector we copy (other).
Output: none.
*/
Vector& Vector::operator=(const Vector& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] this->_elements;

	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;

	this->_elements = new int[this->_capacity];

	for (int i = ZERO; i < this->_capacity; i++)
	{
		this->_elements[i] = other._elements[i];
	}

	return *this;
}

int& Vector::operator[](int n) const
{
	if (n < this->_size && n >= ZERO)
	{
		return this->_elements[n];
	}
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

	if (_size == ZERO)
	{
		cout << "ERROR: pop from empty vector\n";
		return ERROR;
	}

	element = _elements[_size-ONE];
	_elements[_size-ONE] = ZERO;
	_size--;
	return element;
}

/*

*/
void Vector::resize(const int n, const int& val)
{
	resize(n);
	AddValUntilN(val, n);
}

void Vector::assign(const int val)
{
	for (int i = ZERO; i < _capacity; i++)
	{
		_elements[i] = val;
	}
	_size = _capacity;
}

void Vector::AddValUntilN(const int val, const int n)
{
	for (int i = (_capacity - _size - ONE); i < n; i++)
	{
		_elements[i] = val;
	}
	_size = n;
}

/*
Function changes _size to n, unless n is greater than the vector's capacity
Input: const int n
Output: none
*/
void Vector::resize(const int n)
{
	if (n > _capacity)
	{
		reserve(n);
	}
	else
	{
		_size = n;
	}
}

void Vector::reserve(const int n)
{
	int* tempElements = _elements;

	while (_capacity < n)
	{
		_capacity += _resizeFactor;
	}

	_elements = new int[_capacity];

	for (int i = ZERO; i < _size; i++)
	{
		_elements[i] = tempElements[i];
	}

	tempElements = nullptr;
	delete[] tempElements;
}

/*
Function adds an element at the end of the vector.
Input: const int& val (value of the element to add)
Output: none
*/
void Vector::push_back(const int& val)
{
	if (_size == _capacity)
	{
		int* tempElements = _elements;

		_capacity += _resizeFactor;

		_elements = new int[_capacity];

		for (int i = ZERO; i < _size; i++)
		{
			_elements[i] = tempElements[i];
		}
	}

	_elements[_size] = val;
	_size++;
}