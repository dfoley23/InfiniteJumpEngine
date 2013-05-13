#ifndef IJMESSAGE_H
#define IJMESSAGE_H

#include <iostream>
#include "glIncludes.h"

class Component;

class IJMessage
{
public:
	IJMessage(Component*, Component*, char* c, glm::vec3 v = glm::vec3(0.f,0.f,0.f) );
	~IJMessage(void);
	friend class Component;
	std::string getContent(){return content;}
	glm::vec3 getVector(){return vecContent;}
	Component* getReceiver(){return receiver;}
protected:
	Component* sender;
	Component* receiver;
	std::string content;
	glm::vec3 vecContent;
};

#endif