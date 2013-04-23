#ifndef GAME_H
#define GAME_H

#include <vector>
#include "glIncludes.h"
#include "ResManager.h"
#include "Level.h"
#include "Component.h"

class Component; class ResManager;

class Game: public Component
{
public:
	static Game* game(){
		if (!inst){
			inst = new Game();
		}
		return inst;
	}
	~Game(void);
	
	void addComponent(Component* c){
		components.push_back(c);
		c->setParent(this);
	}
	
	Component *getParent(){return NULL;}
	
	int run(int, char**);
	
	int getWinWidth(){return WIN_WIDTH;}
	int getWinHeight(){return WIN_HEIGHT;}

	void setupGLUT();
	void reshape(int, int);
	void display();
	void idle();
	void keyboard(unsigned char, int, int);
	void setupInterface();
	Game * getGame( ){ return this;	};
	Level * buildTestLevel( );

	static void clear(){
		delete inst; inst = NULL;
	}
protected:
	Game(void);
	static Game* inst;

	Level *level;
	ResManager *resman;
	
	componentVector components;
	int WIN_WIDTH, WIN_HEIGHT;
	int main_window;
	GLUI *glui;

	//glui interface variables
	float   transX;
	float   transY;
	float   transZ;
	float   rotX;
	float   rotY;
};

#endif