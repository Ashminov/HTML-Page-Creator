#ifndef __DESCRIPTION__HEADER_INCLUDED__
#define __DESCRIPTION__HEADER_INCLUDED__

#include "Element.h"

class Description : public Element
{
public:
	Description();
	virtual ~Description();

	void setDescrption(const char* description);

	virtual const char* getDescription() const;
	virtual void HTMLstore(ofstream& out)const;

	virtual ElementArray* getElements() override;
	virtual const ElementArray* getElements() const override;

	unsigned int findElement(const char* description) const override;

private:
	void clear();

private:
	char* description;
};

#endif // __DESCRIPTION__HEADER_INCLUDED__
