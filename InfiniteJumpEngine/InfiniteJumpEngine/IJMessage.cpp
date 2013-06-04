#include "IJMessage.h"


IJMessage::IJMessage(Component* s, Component* r, Component* o, const char* c, glm::vec4 v):
	content(c),
	vecContent(v)
{
	sender = s;
	receiver = r;
	other = o;
}


IJMessage::~IJMessage(void)
{
}
