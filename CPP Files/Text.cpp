#include<iostream>
#include"Text.h"
using namespace std;
#include <cstring>

Text::Text()
	:text(nullptr)
{}

Text::Text(const char *description, const char * txt)
{
	set(txt);
	setDescrption(description);
}

Text::Text(const Text & other)
{
	copy(other);
}

Text & Text::operator=(const Text & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Text::~Text()
{
	clear();
}

Element * Text::clone() const
{
	return new Text(*this);
}

void Text::set(const char * txt)
{
	try
	{
		this->text = new char[strlen(txt) + 1];
	}
	catch (bad_alloc&a)
	{
		cerr << "Not enough memory" << endl;
		throw;
	}
	strcpy(this->text, txt);

}

void Text::HTMLstore(ofstream & out) const
{
	out << "<p ";
	Description::HTMLstore(out);
	out << ">" << text << "</p>" << endl;
}

void Text::clear()
{
	delete[]text;
	text = nullptr;
}

void Text::copy(const Text & other)
{
	set(other.text);
	setDescrption(other.getDescription());
}
