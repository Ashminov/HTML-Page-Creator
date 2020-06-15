#include "Div.h"

Div::Div()
{
}

Div::Div(const char* description)
{
	setDescrption(description);
}

Div::Div(const Div& other)
{
	copy(other);
}

Div::~Div()
{
}

Div& Div::operator=(const Div& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}

	return *this;
}

Element* Div::clone() const
{
	return new Div(*this);
}

void Div::HTMLstore(ofstream& out) const
{
	out << "<div ";
	Description::HTMLstore(out);
	out << ">" << endl;
	CompositeBase::HTMLstore(out);
	out << "</div>" << endl;
}
