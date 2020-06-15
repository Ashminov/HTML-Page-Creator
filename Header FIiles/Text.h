#ifndef __TEXT__HEADER__INCLUDED__
#define __TEXT__HEADER__INCLUDED__

#include "Description.h"
class Text:public Description
{
public:

	Text();
	Text(const char *description, const char* txt);
	Text(const Text& other);
	Text& operator=(const Text& other);
	virtual ~Text();

	virtual Element* clone() const override;
	void set(const char* txt);
	virtual void HTMLstore(ofstream& out) const override;

private:

	void clear();
	void copy(const Text& other);


private:
	char* text;


};
#endif // !__TEXT__HEADER__INCLUDED__
