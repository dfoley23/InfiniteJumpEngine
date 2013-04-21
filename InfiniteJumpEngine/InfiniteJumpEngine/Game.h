#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Component.h"

class Component;

class Game: public Component
{
public:
	Game(void);
	~Game(void);
	
	void addComponent(Component* c){
		components.push_back(c);
		c->setParent(this);
	}
	
	Component *getParent(){return NULL;}
	Game *getGame(){return this;}
	
	int run(int, char**);
	
	int getWinWidth(){return WIN_WIDTH;}
	int getWinHeight(){return WIN_HEIGHT;}

	void reshape(int, int);
	void display();
	void idle();
	void keyboard(unsigned char, int, int);
protected:
	componentVector components;
	int WIN_WIDTH, WIN_HEIGHT;
};

#endif