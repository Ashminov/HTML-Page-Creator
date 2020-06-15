#ifndef __DIV__HEADER_INCLUDED__
#define __DIV__HEADER_INCLUDED__

#include "CompositeBase.h"

class Div : public CompositeBase
{
public:
	Div();
	Div(const char *description);
	Div(const Div& other);
	virtual ~Div();

	Div& operator=(const Div& other);

	virtual Element* clone() const override;
	virtual void HTMLstore(ofstream& out) const override;
};

#endif // __DIV__HEADER_INCLUDED__
