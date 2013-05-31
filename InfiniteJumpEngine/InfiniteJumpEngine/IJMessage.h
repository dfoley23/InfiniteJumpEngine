#pragma once
#ifndef IJMESSAGE_H
#define IJMESSAGE_H

#include <iostream>
#include "glIncludes.h"

class Component;

class IJMessage
{
public:
	IJMessage(Component*, Component*, Component*, const char* c, glm::vec4 v = glm::vec4(0.f,0.f,0.f,0.f) );
	~IJMessage(void);
	friend class Component;
	std::string getContent(){return content;}
	glm::vec4 getVector(){return vecContent;}
	Component* getReceiver(){return receiver;}
	Component* getOther(){return other;}
protected:
	Component* sender;
	Component* receiver;
	Component* other;
	std::string content;
	glm::vec4 vecContent;
};

#endif IJMESSAGE_H