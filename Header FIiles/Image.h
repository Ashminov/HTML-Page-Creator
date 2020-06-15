#ifndef __IMAGE__HEADER__INCLUDED__
#define __IMAGE__HEADER__INCLUDED__

#include "Description.h"
class Image:public Description
{

public:
	Image();
	Image(const char*description, const char*path);
	Image(const Image &other);
	Image &operator=(const Image&other);
	virtual ~Image();

	virtual Element* clone() const override;
	virtual void HTMLstore(ofstream& out) const override;
	void set(const  char*imagepath);

private:

	void clear();
	void copy(const Image& other);

private:

	char *image;

};
#endif // !__IMAGE__HEADER__INCLUDED__
