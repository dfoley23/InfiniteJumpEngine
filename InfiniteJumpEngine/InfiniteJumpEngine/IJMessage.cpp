#include "IJMessage.h"


IJMessage::IJMessage(Component* s, Component* r, char* c, glm::vec3 v):
	content(c),
	vecContent(v)
{
	sender = s;
	receiver = r;
}


IJMessage::~IJMessage(void)
{
}
