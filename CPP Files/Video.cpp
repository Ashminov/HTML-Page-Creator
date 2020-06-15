#include<iostream>
#include "Video.h"
using namespace std;
const int widthsize = 560;
const int heightsize = 320;
#include <cstring>

Video::Video()
	:URL(nullptr)

{}

Video::Video(const char *description, const char * url)
{
	set(url);
	setDescrption(description);
}

Video::Video(const Video & other)
{
	copy(other);
}

Video & Video::operator=(const Video & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Video::~Video()
{
	clear();
}

Element * Video::clone() const
{
	return new Video(*this);
}

void Video::set(const char * url)
{

	try
	{
		this->URL = new char[strlen(url) + 1];
	}
	catch (bad_alloc&a)
	{
		cerr << "Not enough memory" << endl;
		throw;
	}
	strcpy(this->URL, url);
}

void Video::HTMLstore(ofstream & out) const
{
	out << "<iframe ";
	Description::HTMLstore(out);
	out << " src=\"" << URL << "\" allowfullscreen>" << "</iframe>" << endl;
}

void Video::clear()
{
	delete[]URL;
	URL = nullptr;
}

void Video::copy(const Video & other)
{
	set(other.URL);
	setDescrption(other.getDescription());
}
