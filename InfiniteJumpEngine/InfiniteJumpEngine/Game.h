#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Component.h"
#include "glIncludes.h"
#include "ResManager.h"
#include "Level.h"

class ResManager;

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
	void setupInterface(void(*cb)(int i));
	void glui_callBack( int id );
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
	bool    cupInput;
	float   camEyeX;
	float   camEyeY;
	float   camEyeZ;
	float   camLookAtX;
	float   camLookAtY;
	float   camLookAtZ;
	bool    camInput;
};

#endif