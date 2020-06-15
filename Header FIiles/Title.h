#ifndef __TITLE__HEADER__INCLUDED__
#define __TITLE__HEADER__INCLUDED__

#include "Description.h"

class Title:public Description
{

public:

	Title();
	Title(const char *description, const char* Words);
	Title(const Title &other);
	Title &operator =(const Title &other);
	virtual ~Title();

	virtual Element *clone()const override;
	void set(const  char*Words);
	virtual void HTMLstore(ofstream& out) const override;

private:

	void clear();
	void copy(const Title& other);


private:

	char* words;

};
#endif // !__TITLE__HEADER__INCLUDED__
