#ifndef __DOCUMENT__HEADER_INCLUDED__
#define __DOCUMENT__HEADER_INCLUDED__

#include "CompositeBase.h"

class Document : public CompositeBase
{
public:
	Document();
	Document(const Document& other);
	virtual ~Document();

	Document& operator=(const Document& other);

	virtual Element* clone() const override;
	virtual void HTMLstore(ofstream& out) const override;
};

#endif // __DOCUMENT__HEADER_INCLUDED__
