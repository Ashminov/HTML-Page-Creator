#ifndef __LINK__HEADER__INCLUDED__
#define __LINK__HEADER__INCLUDED__

#include "Description.h"
class Link:public Description
{

public:
	Link();
	Link(const char *description, const char *url, const char*text);
	Link(const Link&other);
	Link &operator=(const Link&other);
	virtual ~Link();

	virtual Element* clone() const override;
	void set(const char*url, const char*text);
	virtual void HTMLstore(ofstream& out) const override;


private:

	void copy(const Link&other);
	void clear();

private:

	char * url;
	char * text;

};
#endif // !__LINK__HEADER__INCLUDED__
