#include<iostream>
#include "Image.h"
using namespace std;
#include <cstring>

const int HeightSize = 300;
const int WidthSize = 350;
Image::Image()
	:image(nullptr)
{

}

Image::Image(const char*description, const char*path)
{
	set(path);
	setDescrption(description);
}

Image::Image(const Image & other)
{
	copy(other);
}

Image & Image::operator=(const Image & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}

	return *this;
}

Image::~Image()
{
	clear();
}

Element *Image::clone() const
{
	return new Image(*this);
}

void Image::HTMLstore(ofstream & out) const
{
	out << "<img ";
	Description::HTMLstore(out);
	out << " src=\"" << image << "\">" << endl;
}

void Image::set(const char * imagepath)
{
	try {
		this->image = new char[strlen(imagepath) + 1];
	}
	catch (bad_alloc&a)
	{
		cerr << "Not enough memory" << endl;
		throw;
	}
	strcpy(this->image, imagepath);
}

void Image::clear()
{
	delete[]image;
	image = nullptr;
}

void Image::copy(const Image & other)
{
	set(other.image);
	setDescrption(other.getDescription());
}
