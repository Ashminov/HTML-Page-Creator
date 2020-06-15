#ifndef __SYSTEM__HEADER__INCLUDED__
#define __SYSTEM__HEADER__INCLUDED__

#include "Document.h"

class System
{
public:
	System();
	~System();

	void Input();

	void Process(char* params, Element* container);

private:
	static char* GetToken(char** line);
	static char* GetTriToken(char** line);

private:
	void HandleExit();
	void HandlePrint(Element* container);
	void HandleSave(char* params);
	void HandleLoad(char* params);
	void HandleWith(char* params, Element* container);
	void HandleAdd(char* params, Element* container);
	void HandleAddHeading(const char* description, const char* heading, Element* container);
	void HandleAddText(const char* description, const char* text, Element* container);
	void HandleAddVideo(const char* description, const char* url, Element* container);
	void HandleAddImage(const char* description, const char* image, Element* container);
	void HandleAddLink(const char* description, char* params, Element* container);
	void HandleAddContainer(const char* description, Element* container);
	void HandleRemove(char* params, Element* container);
	void HandleMoveTo(char* params, Element* container);

private:
	void DoSave(const char* filename);
	void DoLoad(const char* filename);
	void DoWith(char* params, Element* container);
	void DoAdd(Element* element, Element* container);
	void DoRemove(unsigned int index, Element* container);
	void DoMoveTo(unsigned int fromIndex, unsigned int toIndex, Element* container);

private:
	void clear();

private:
	bool running;
	bool changed;
	char* outname;
	Document* document;
};

#endif // !__SYSTEM__HEADER__INCLUDED__
