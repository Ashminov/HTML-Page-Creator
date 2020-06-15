#include "Document.h"

Document::Document()
{
}

Document::Document(const Document& other)
{
	copy(other);
}

Document::~Document()
{
}

Document& Document::operator=(const Document& other)
{
	if (this != &other) {
        clear();
        copy(other);
	}

	return *this;
}

Element* Document::clone() const
{
	return new Document(*this);
}

void Document::HTMLstore(ofstream& out) const
{
	out << "<!DOCTYPE html>" << endl;
	out << "<html>" << endl;
	out << "<head> </head>" << endl;
	out << "<body>" << endl;
	CompositeBase::HTMLstore(out);
	out << "</body>" << endl;
	out << "</html>" << endl;
}
