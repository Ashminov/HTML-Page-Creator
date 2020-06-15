#include<iostream>
#include "Title.h"
using namespace std;
#include <cstring>

Title::Title()
	:words(nullptr)
{
}

Title::Title(const char *description, const char * Words)
{
	set(Words);
	setDescrption(description);
}

Title::Title(const Title & other)
{
	copy(other);
}

Title & Title::operator=(const Title & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Title::~Title()
{
	clear();
}

Element * Title::clone() const
{
	return new Title(*this);
}

void Title::set(const char * Words)
{
	try
	{
		this->words = new char[strlen(Words) + 1];
	}
	catch (bad_alloc&a)
	{
		cerr << "Not enough Memory" << endl;
		throw;
	}
	strcpy(this->words, Words);
}

void Title::HTMLstore(ofstream & out) const
{
	out << "<h1 ";
	Description::HTMLstore(out);
	out << ">" << words << "</h1>"<< endl;
}

void Title::clear()
{
	delete[]words;
	words = nullptr;
}

void Title::copy(const Title & other)
{
	set(other.words);
	setDescrption(other.getDescription());
}
