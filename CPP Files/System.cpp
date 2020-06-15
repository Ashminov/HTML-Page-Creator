#include "System.h"

#include "Image.h"
#include "Link.h"
#include "Text.h"
#include "Title.h"
#include "Video.h"
#include "Div.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

System::System()
	: running(false)
	, changed(false)
	, outname(nullptr)
	, document(nullptr)
{
}

System::~System()
{
	clear();
}

char* System::GetToken(char** line)
{
	char* start = *line;

	// skip space
	while (*start && isspace(*start)) {
		start++;
	}

	char* end = start;

	// skip letters
	while (*end && !isspace(*end)) {
		end++;
	}

	// adjust next token position
	if (*end) {
		*line = end + 1;
	} else {
		*line = end;
	}

	// terminate current token
	*end = 0;

	return start;
}

char* System::GetTriToken(char** line)
{
	char* start = *line;

	// skip space
	while (*start && isspace(*start)) {
		start++;
	}

	if (*start == '<') {
		// skip open bracket
		start++;

		// scan for closing bracket
		char* end = start;
		while (*end && *end != '>') {
			end++;
		}

		if (*end == '>') {
			// adjust next token position
			char* next = end + 1;
			while (*next && isspace(*next)) {
				next++;
			}
			*line = next;

			// terminate current token
			*end = 0;

			return start;
		}
		else {
			return *line;
		}
	}
	else {
		return *line;
	}
}

void System::Input()
{
	char buffer[1024];

	running = true;
	while (running) {
		cout << endl << "> ";
		cin.getline(buffer, sizeof(buffer));

		Process(buffer, document);
	}
}

void System::Process(char* params, Element* container)
{
	char* command = GetToken(&params);
	if (!*command) {
		cout << "Command is expected" << endl;
		return;
	}

	if (strcmp(command, "exit") == 0) {
		HandleExit();
	}
	else if (strcmp(command, "print") == 0) {
		HandlePrint(container);
	}
	else if (strcmp(command, "save") == 0) {
		HandleSave(params);
	}
	else if (strcmp(command, "load") == 0) {
		HandleLoad(params);
	}
	else if (strcmp(command, "with") == 0) {
		HandleWith(params, container);
	}
	else if (strcmp(command, "add") == 0) {
		HandleAdd(params, container);
	}
	else if (strcmp(command, "remove") == 0) {
		HandleRemove(params, container);
	}
	else if (strcmp(command, "moveTo") == 0) {
		HandleMoveTo(params, container);
	}
	else {
		cout << "Invalid command " << command << endl;
	}
}

void System::HandleExit()
{
	running = false;

	if (outname && changed) {
		DoSave(outname);
	}
}

void System::HandlePrint(Element* container)
{
	if (!container) {
		cerr << "Document is not loaded" << endl;
		return;
	}

	cout << "Document contents:" << endl;
	const ElementArray& els = *container->getElements();
	unsigned int nels = els.getSize();
	for (unsigned int i = 0; i < nels; ++i) {
		cout << "description " << els[i]->getDescription() << ", position " << i << endl;
	}
}

void System::HandleSave(char* params)
{
	char* filename = GetToken(&params);
	if (!*filename) {
		if (!outname) {
			cerr << "File is not loaded" << endl;
			return;
		}
		filename = outname;
	}
	DoSave(filename);
}

void System::HandleLoad(char* params)
{
	char* filename = GetToken(&params);
	if (!*filename) {
		cerr << "File is not specified" << endl;
	}

	DoLoad(filename);
}

void System::HandleWith(char* params, Element* container)
{
	if (!container) {
		cerr << "Document is not loaded" << endl;
		return;
	}

	char* description = GetTriToken(&params);
	if (description == params) {
		cerr << "Description is expected" << endl;
		return;
	}

	unsigned int nel = container->findElement(description);
	if (nel == ElementArray::invalid) {
		cerr << "Element with description " << description << " is not found" << endl;
		return;
	}

	Element* el = (*container->getElements())[nel];
	if (!el->getElements()) {
		cerr << "Element with description " << description << " has no children" << endl;
		return;
	}

	DoWith(params, el);
}

void System::HandleAdd(char* params, Element* container)
{
	if (!container) {
		cerr << "Document is not loaded" << endl;
		return;
	}

	char* tag = GetToken(&params);
	if (!*tag) {
		cerr << "Tag type is expected" << endl;
		return;
	}

	char* description = GetTriToken(&params);
	if (description == params) {
		cerr << "Description is expected" << endl;
		return;
	}

	if (container->findElement(description) != ElementArray::invalid) {
		cerr << "Description " << description << " is already taken" << endl;
		return;
	}

	if (strcmp(tag, "heading") == 0) {
		HandleAddHeading(description, params, container);
	}
	else if (strcmp(tag, "text") == 0) {
		HandleAddText(description, params, container);
	}
	else if (strcmp(tag, "video") == 0) {
		HandleAddVideo(description, params, container);
	}
	else if (strcmp(tag, "image") == 0) {
		HandleAddImage(description, params, container);
	}
	else if (strcmp(tag, "link") == 0) {
		HandleAddImage(description, params, container);
	}
	else if (strcmp(tag, "container") == 0) {
		HandleAddContainer(description, container);
	}
	else {
		cerr << "Invalid tag type" << tag << endl;
	}
}

void System::HandleAddHeading(const char* description, const char* heading, Element* container)
{
	if (!*heading) {
		cerr << "Heading is expected" << endl;
		return;
	}

	DoAdd(new Title(description, heading), container);
}

void System::HandleAddText(const char* description, const char* text, Element* container)
{
	if (!*text) {
		cerr << "Text is expected" << endl;
		return;
	}

	DoAdd(new Text(description, text), container);
}

void System::HandleAddVideo(const char* description, const char* url, Element* container)
{
	if (!*url) {
		cerr << "URL is expected" << endl;
		return;
	}

	DoAdd(new Video(description, url), container);
}

void System::HandleAddImage(const char* description, const char* image, Element* container)
{
	if (!*image) {
		cerr << "Image is expected" << endl;
		return;
	}

	DoAdd(new Image(description, image), container);
}

void System::HandleAddLink(const char* description, char* params, Element* container)
{
	char* link = GetToken(&params);
	if (!*link) {
		cerr << "Link is expected" << endl;
		return;
	}

	char* text = params;
	if (!*text) {
		cerr << "Text is expected" << endl;
		return;
	}

	DoAdd(new Link(description, link, text), container);
}

void System::HandleAddContainer(const char* description, Element* container)
{
	DoAdd(new Div(description), container);
}

void System::HandleRemove(char* params, Element* container)
{
	if (!container) {
		cerr << "Document is not loaded" << endl;
		return;
	}

	char* description = GetTriToken(&params);
	if (description == params) {
		cerr << "Description is expected" << endl;
		return;
	}

	unsigned int nel = container->findElement(description);
	if (nel == ElementArray::invalid) {
		cerr << "Element with description " << description << " is not found" << endl;
		return;
	}

	DoRemove(nel, container);
}

void System::HandleMoveTo(char* params, Element* container)
{
	if (!container) {
		cerr << "Document is not loaded" << endl;
		return;
	}

	char* pos = GetToken(&params);
	if (!*pos) {
		cerr << "Position is expected" << endl;
		return;
	}

	char* description = GetTriToken(&params);
	if (description == params) {
		cerr << "Description is expected" << endl;
		return;
	}

	unsigned int nel = container->findElement(description);
	if (nel == ElementArray::invalid) {
		cerr << "Element with description " << description << " is not found" << endl;
		return;
	}

	DoMoveTo(nel, atoi(pos), container);
}

void System::DoSave(const char* filename)
{
	ofstream out(filename, ios::out|ios::trunc);
	document->HTMLstore(out);
	out.close();
	changed = false;
}

void System::DoLoad(const char* filename)
{
	if (outname && changed)
	{
		DoSave(outname);
	}

	clear();
	try {
		outname = new char[strlen(filename) + 1];
		document = new Document();
	}
	catch (bad_alloc& e) {
		cerr << "Not enough memory" << endl;
		throw;
	}

	strcpy(outname, filename);
}

void System::DoWith(char* params, Element* container)
{
	Process(params, container);
}

void System::DoAdd(Element* element, Element* container)
{
	container->getElements()->add(element);
	changed = true;
}

void System::DoRemove(unsigned int index, Element* container)
{
	container->getElements()->remove(index);
	changed = true;
}

void System::DoMoveTo(unsigned int fromIndex, unsigned int toIndex, Element* container)
{
	if (fromIndex == toIndex) {
		return;
	}

	ElementArray& els = *container->getElements();
	Element* el = els[fromIndex];
    els.remove(fromIndex);
    els.insert(toIndex, el);
    changed = true;
}

void System::clear()
{
	delete [] outname;
	outname = nullptr;

	delete document;
	document = nullptr;
}
