#include "Vector.h"

using namespace std;

//=================================
//констуркторы, деструкторы, операторы класса Vector
Vector::Vector(const Value* rawArray, const size_t size, float coef): _size(size),
								      _capacity(size), 
								      _multiplicativeCoef(coef)
{
	_data = new Value[_size];
	for(int i = 0; i < size; i++)
	{
		_data[i] = rawArray[i];
	}
}

//=================================
Vector::Vector(const Vector& other): _size(other._size),
				     _capacity(other._size),
				     _multiplicativeCoef(other._multiplicativeCoef)
{
	if(&other == this)
	{
		return;
	}
	
	_data = new Value[other._size];
	for(int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}
}

//=================================
Vector& Vector::operator=(const Vector& other)
{
	if(&other == this)
	{
		return *this;
	}
	
	delete[] _data;
	_size = other._size;
	_capacity = other._size;
	_multiplicativeCoef = other._multiplicativeCoef;
	_data = new Value[other._size];
	for(int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}
	
	return *this;
}

//=================================
Vector::Vector(Vector&& other) noexcept
{
	_size = other._size;
	_capacity = other._capacity; 
	_multiplicativeCoef = other._multiplicativeCoef; 
	_data = other._data;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 2.0f;
}

//=================================
Vector& Vector::operator=(Vector&& other) noexcept
{
	if(&other == this)
	{
		return *this;
	}
	
	_size = other._size;
	_capacity = other._capacity; 
	_multiplicativeCoef = other._multiplicativeCoef; 
	_data = other._data;
	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 2.0f;
	
	return *this;
}

//=================================
Value& Vector::operator[](size_t idx)
{
	return _data[idx];
}

//=================================
const Value& Vector::operator[](size_t idx) const
{
	return _data[idx];
}

//=================================
Vector::~Vector()
{
	delete[] _data; 
	_size = 0; 
	_capacity = 0; 
	_multiplicativeCoef = 2.0f; 
}

//=================================
//моя функция для сокращения кода
void Vector::allocateNewMemory(int number)
{
	if(_capacity <= _size - number)
	{
		Value* new_mass = new Value[_capacity];
		if(_capacity < 1)
		{
			_capacity = 1;
		}
		_capacity *= _multiplicativeCoef;
		for(size_t i = 0; i < _size - number; i++)
		{
			new_mass[i] = _data[i];
		}
		_data = new Value[_capacity];
		for(size_t i = 0; i < _size - number; i++)
		{
			_data[i] = new_mass[i];
		}
	}
}

//=================================
//функции
//=================================
void Vector::pushBack(const Value& value)
{
	_size += 1;
	allocateNewMemory(1);
	
	_data[_size - 1] = value;
}
	
//=================================
void Vector::pushFront(const Value& value)
{
	_size += 1;
	allocateNewMemory(1);
	
	for(size_t i = _size - 1; i > 0; i--)
	{
		_data[i] = _data[i - 1];
	}
	
	_data[0] = value;
}

//=================================
void Vector::insert(const Value& value, size_t pos)
{
	_size += 1;
	allocateNewMemory(1);
	
	for(size_t i = _size - 1; i > pos; i--)
	{
		_data[i] = _data[i - 1];
	}
	
	_data[pos] = value;
}

//=================================
void Vector::insert(const Value* values, size_t size, size_t pos){
	
	_size += size;
	allocateNewMemory(size);
	
	int count = 1;
	for(size_t i = _size - 1; i >= size; i--)
	{
		int PosToSwap = _size - size - count;
	    _data[i] = _data[PosToSwap];
		count++;
	}
	
	for(size_t i = 0; i < size; i++)
	{
		_data[pos + i] = values[i];
	}
}

//=================================
void Vector::insert(const Vector& vector, size_t pos)
{
	insert(vector._data, vector._size, pos);
}

//=================================
void Vector::popBack()
{
	if(_size == 0)
	{
		throw out_of_range("Emty vector");
	}
	else
	{
		_size -= 1;
	}
}

//=================================
void Vector::popFront()
{
	if(_size == 0)
	{
		throw out_of_range("Emty vector");
	}
	else
	{
		for(int i = 0; i < _size; i++)
		{
			_data[i] = _data[i + 1];
		}
		
		_size -= 1;
	}
}

//=================================
void Vector::erase(size_t pos, size_t count)
{
	if(_size == 0)
	{
		throw out_of_range("Emty vector");
	}
	else
	{
		if (count + pos > _size)
		{
        _size = _size - (_size - pos);
    	}
		else
		{
        	for (size_t i = 0; i < _size  - count + 1; i++)
			{
				int PosToSwap = i + pos + count;
            	_data[i + pos] = _data[PosToSwap];
        	}
		_size -= count;
    	}
	}
}

//=================================
void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
	erase(beginPos, endPos - beginPos + 1);
}

//=================================
size_t Vector::size() const
{
	return _size;
}

//=================================
size_t Vector::capacity() const
{
	return _capacity;
}

//=================================
double Vector::loadFactor() const
{
    return static_cast<double>(_size) / _capacity;
}

//=================================
long long Vector::find(const Value& value) const
{
	int counter = 0;
	for(int i = 0; i < _size; i++)
	{
		if(_data[i] != value)
		{
			counter++;
		}
		else
		{
			break;
		}
	}
	if(counter < _size)
	{
		return counter;
	}
	else
	{
		return -1;
	}
}

//=================================
void Vector::reserve(size_t capacity)
{
	if(capacity > 1)
	{
		if(capacity > _capacity)
		{
			_capacity = capacity;
			Value* new_mass = new Value[_capacity];
			for(size_t i = 0; i < _size; i++)
			{
				new_mass[i] = _data[i];
			}

			_data = new_mass;
		}	
	}
}

//=================================
void Vector::shrinkToFit()
{
	_capacity = _size;
	
	Value* new_mass = new Value[_size];
	for(size_t i = 0; i < _size; i++)
	{
		new_mass[i] = _data[i];
	}
	
	delete[] _data;
	_data = new_mass;
}

//=================================
//операторы класса Iterator
Value& Iterator::operator*()
{
	return *_ptr;
}

//=================================
const Value& Iterator::operator*() const
{
	return *_ptr;
}

//=================================
Value* Iterator::operator->()
{
	return _ptr;
}

//=================================
const Value* Iterator::operator->() const
{
	return _ptr;
}

//=================================
Iterator Iterator::operator++()
{
	++_ptr;
	return *this;
}

//=================================
Iterator Iterator::operator++(int)
{
	Value* m =_ptr;
	++_ptr;
	return Iterator(m);
}

//=================================
bool Iterator::operator==(const Iterator& other) const
{
	return _ptr == other._ptr;
}

//=================================
bool Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

//=================================
Iterator Vector::begin()
{
	return Iterator(&_data[0]);
}

//=================================
Iterator Vector::end()
{
	return Iterator(&_data[_size]);
}
