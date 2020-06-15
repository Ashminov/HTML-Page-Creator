#ifndef __DYNAMICARRAY__HEADER_INCLUDED__
#define __DYNAMICARRAY__HEADER_INCLUDED__

#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
public:
	static const unsigned int invalid = (unsigned int)-1;

public:
	DynamicArray();
	DynamicArray(const DynamicArray& other);
	~DynamicArray();

	DynamicArray& operator=(const DynamicArray& other);

	void setCapacity(unsigned int newCapacity);

	void setSize(unsigned int newSize);
	unsigned int getSize() const;

	void add(const T& element);
	void insert(unsigned int at, const T& element);
	void remove(unsigned int index);

	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;

	void clear();

private:
	void checkRange(unsigned int index) const;
	void copy(const DynamicArray& other);

private:
	unsigned int size;
	unsigned int capacity;
	T* array;
};

template <class T>
DynamicArray<T>::DynamicArray()
	: size(0)
	, capacity(0)
	, array(nullptr)
{
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
    copy(other);
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
	clear();
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (this != &other){
		clear();
		copy(other);
	}

	return *this;
}

template <class T>
void DynamicArray<T>::setCapacity(unsigned int newCapacity)
{
	if (capacity < size) {
		throw range_error("capacity");
	}

	T* newArray = nullptr;
	try {
		newArray = new T[newCapacity];
	}
	catch (bad_alloc&a) {
		cerr << "Not enough memory" << endl;
		throw;
	}

	for (unsigned int i = 0; i < size; ++i) {
		newArray[i] = array[i];
	}
	delete [] array;
	array = newArray;
	capacity = newCapacity;
}

template <class T>
void DynamicArray<T>::setSize(unsigned int newSize)
{
	if (newSize > capacity) {
		if (newSize > 2 * capacity) {
			setCapacity(newSize);
		} else {
			setCapacity(2 * capacity);
		}
	}
	size = newSize;
}

template <class T>
unsigned int DynamicArray<T>::getSize() const
{
	return size;
}

template <class T>
void DynamicArray<T>::add(const T& element)
{
	unsigned int at = size;
	setSize(size+1);
	array[at] = element;
}

template <class T>
void DynamicArray<T>::insert(unsigned int at, const T& element)
{
	if (at != size) {
		checkRange(at);
	}

	setSize(size+1);

	for (unsigned int i = size - 1; i > at; --i) {
		array[i] = array[i - 1];
	}

	array[at] = element;
}

template <class T>
void DynamicArray<T>::remove(unsigned int index)
{
	checkRange(index);

	for (unsigned int i = index; i < size; ++i) {
		array[i] = array[i + 1];
	}

	setSize(size - 1);
}

template <class T>
T& DynamicArray<T>::operator[](unsigned int index)
{
	checkRange(index);
	return array[index];
}

template <class T>
const T& DynamicArray<T>::operator[](unsigned int index) const
{
	checkRange(index);
	return array[index];
}

template <class T>
void DynamicArray<T>::clear()
{
	delete [] array;
	array = nullptr;
	size = 0;
	capacity = 0;
}

template <class T>
void DynamicArray<T>::checkRange(unsigned int index) const
{
	if (index >= size) {
		throw out_of_range("remove");
	}
}

template <class T>
void DynamicArray<T>::copy(const DynamicArray<T>& other)
{
	setCapacity(other.capacity);
	size = other.getSize();
	for (unsigned int i = 0; i < size; ++i) {
		array[i] = other.array[i];
	}
}

#endif // __DYNAMICARRAY__HEADER_INCLUDED__
