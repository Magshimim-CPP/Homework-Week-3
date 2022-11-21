#include "Vector.h"

using namespace std;

#define ZERO 0
#define ERROR -9999
#define ONE 1
#define TWO 2

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

Vector::~Vector()
{
	delete[] _elements;
}

int Vector::size() const
{
	return _size;
}

int Vector::capacity() const 
{
	return _capacity;
}

bool Vector::empty() const
{
	return _size <= ZERO;
}

int Vector::resizeFactor() const
{
	return _resizeFactor;
}

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

void Vector::resize(const int n)
{
	if (n > _capacity)
	{
		reserve(n);
	}
	else
	{
		_size = n;

		int* tempElements = _elements;

		_elements = new int[_capacity];

		for (int i = ZERO; i < _size; i++)
		{
			_elements[i] = tempElements[i];
		}

		delete[] tempElements;
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