#include <iostream>
#include <cstring>
#include "CompositeBase.h"
using namespace std;

CompositeBase::CompositeBase()
	: elements()
{
}

CompositeBase::CompositeBase(const CompositeBase & other)
{
	copy(other);
}

CompositeBase & CompositeBase::operator=(const CompositeBase & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

CompositeBase::~CompositeBase()
{
	clear();
}

void CompositeBase::HTMLstore(ofstream & out) const
{
	unsigned int max = elements.getSize();
	for (unsigned int i = 0; i < max; ++i) {
		elements[i]->HTMLstore(out);
		out << "<br>" << endl;
	}
}

void CompositeBase::copy(const CompositeBase & other)
{
	unsigned int max = other.elements.getSize();
	elements.setCapacity(max);
	for (unsigned int i = 0; i < max; ++i) {
		elements.add(other.elements[i]->clone());
	}
}

void CompositeBase::clear()
{
	unsigned int max = elements.getSize();
	for (unsigned int i = 0; i < max; ++i) {
		delete elements[i];
	}
	elements.clear();
}

ElementArray* CompositeBase::getElements()
{
	return &elements;
}

const ElementArray* CompositeBase::getElements() const
{
	return &elements;
}

unsigned int CompositeBase::findElement(const char* description) const
{
	unsigned int nels = elements.getSize();
	for (unsigned int i = 0; i < nels; ++i) {
        if (strcmp(elements[i]->getDescription(), description) == 0) {
			return i;
        }
	}

	return ElementArray::invalid;
}
