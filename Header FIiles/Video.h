#ifndef __VIDEO__HEADER__INCLUDED__
#define __VIDEO__HEADER__INCLUDED__

#include "Description.h"

class Video:public Description
{

public:

	Video();
	Video(const char *description, const char *url);
	Video(const Video&other);
	Video &operator=(const Video&other);
	virtual ~Video();

	virtual Element*clone() const override;
	void set(const  char*url);
	virtual void HTMLstore(ofstream& out) const override;

private:

	void clear();
	void copy(const Video& other);


private:
	char*URL;

};
#endif // !__VIDEO__HEADER__INCLUDED__
