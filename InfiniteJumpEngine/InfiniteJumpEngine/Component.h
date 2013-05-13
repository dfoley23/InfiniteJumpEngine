#pragma once

#include "IJMessage.h"
#include "Drawable.h"
#include <vector>

class Component: public Drawable
{
public:
	Component(){
		parent = NULL;
	}
	virtual Component * getParent(){return parent;};
	virtual void setParent(Component * p){parent = p;};
	virtual glm::mat4 transform(void){
		return transform(glm::mat4());
	}
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			return parent->transform(in);
		return in;
	}
	virtual glm::vec3 getPickId( ) {
		return pickId;
	}

	virtual void sendMessage(Component* that, char *s, glm::vec3 v = glm::vec3(0,0,0)){
		IJMessage *m =  new IJMessage(this, that, s, v);
		sendMessage(m, that);
		delete m; m = NULL;
	}

	virtual void sendMessage( IJMessage *m, Component* that){
		if (that){
			that->receiveMessage(m);
		} else {
			cout << "Message fell out of parent chain:" << m->content << endl;
		}
	}
	virtual void receiveMessage( IJMessage *m ){
		sendMessage(m, parent);
	}
protected:
	Component *parent;
	glm::vec3 pickId;
};

typedef std::vector<Component*> componentVector;
typedef componentVector::iterator componentIter;