#ifndef __ELEMENT__HEADER__INCLUDED__
#define __ELEMENT__HEADER__INCLUDED__
#include <fstream>
using namespace std;

#include "DynamicArray.hpp"

class Element;
typedef DynamicArray<Element*> ElementArray;

class Element
{
public:
	virtual ~Element(){}
	virtual Element* clone() const = 0;
	virtual void HTMLstore(ofstream& out)const = 0;
	virtual const char* getDescription() const = 0;

	virtual ElementArray* getElements() = 0;
	virtual const ElementArray* getElements() const = 0;

	virtual unsigned int findElement(const char* description) const = 0;
};

#endif // !__ELEMENT__HEADER__INCLUDED__
