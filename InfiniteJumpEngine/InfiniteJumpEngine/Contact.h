#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#include "glIncludes.h"

class Collider;

class Contact
{
public:
	Contact(Collider*, Collider*, glm::vec3, glm::vec3);
	~Contact(void);
	Collider *objectA, *objectB;
	glm::vec3 normalA, normalB;
};

#endif CONTACT_H