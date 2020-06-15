#ifndef __COMPOSITEBASE__HEADER__INCLUDED__
#define __COMPOSITEBASE__HEADER__INCLUDED__

#include "Description.h"

class CompositeBase:public Description
{
public:
	CompositeBase();
	CompositeBase(const CompositeBase &other);
	CompositeBase &operator=(const CompositeBase &other);
	virtual ~CompositeBase();

	virtual void HTMLstore(ofstream& out) const override;

	virtual ElementArray* getElements() override;
	virtual const ElementArray* getElements() const override;

	unsigned int findElement(const char* description) const override;

protected:
	void copy(const CompositeBase &other);
	void clear();

private:
	ElementArray elements;
};

#endif
