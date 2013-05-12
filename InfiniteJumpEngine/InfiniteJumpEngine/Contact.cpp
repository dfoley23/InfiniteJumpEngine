#include "Contact.h"

Contact::Contact(Collider* a, Collider* b, glm::vec3 nA, glm::vec3 nB)
{
	objectA = a;
	objectB = b;
	normalA = nA;
	normalB = nB;
}


Contact::~Contact(void)
{
}
