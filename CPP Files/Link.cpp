#include <iostream>
using namespace std;
#include "Link.h"
#include <cstring>

Link::Link()
	:url(nullptr)
	,text(nullptr)
{}
Link::Link(const char *description, const char *url, const char*text)
{
	set(url, text);
	setDescrption(description);
}

Link::Link(const Link & other)
{
	copy(other);
}

Link & Link::operator=(const Link & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Link::~Link()
{
	clear();
}

Element * Link::clone() const
{
	return new Link(*this);
}

void Link::set(const char * url, const char * text)
{
	try {
		this->url = new char[strlen(url) + 1];
		this->text = new char[strlen(text) + 1];
	}
	catch (bad_alloc&a)
	{
		cerr << "Not enough memory" << endl;
		throw;
	}
	strcpy(this->url, url);
	strcpy(this->text, text);

}

void Link::HTMLstore(ofstream & out) const
{
	out << "<a ";
	Description::HTMLstore(out);
	out << " href=\"" << url << "\">" << text << "</a>" << endl;
}

void Link::copy(const Link & other)
{
	set(other.url, other.text);
	setDescrption(other.getDescription());
}

void Link::clear()
{
	delete[]url;
	url = nullptr;
	delete[]text;
	text = nullptr;
}
