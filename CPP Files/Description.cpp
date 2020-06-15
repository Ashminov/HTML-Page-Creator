#include "Description.h"
#include <stdexcept>
#include <cstring>
#include <iostream>
using namespace std;

Description::Description()
	: description(nullptr)
{
}

Description::~Description()
{
	clear();
}

void Description::setDescrption(const char* description)
{
	clear();
	try {
		this->description = new char[strlen(description) + 1];
	}
	catch (bad_alloc& e) {
		cerr << "Not enough Memory" << endl;
		throw;
	}
	strcpy(this->description, description);
}

const char* Description::getDescription() const
{
	return description;
}

void Description::HTMLstore(ofstream& out) const
{
	out << "descr=\"" << description << "\"";
}

ElementArray* Description::getElements()
{
	return nullptr;
}

const ElementArray* Description::getElements() const
{
	return nullptr;
}

unsigned int Description::findElement(const char* description) const
{
	return ElementArray::invalid;
}

void Description::clear()
{
	delete [] description;
	description = nullptr;
}
