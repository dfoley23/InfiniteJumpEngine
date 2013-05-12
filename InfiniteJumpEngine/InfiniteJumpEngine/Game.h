#ifndef GAME_H
#define GAME_H

#include <vector>
#include "IJTime.h"
#include "IJMessage.h"
#include "Component.h"
#include "glIncludes.h"
#include "ResManager.h"

#define PIXEL(c,x,y,w)	(c[(x)+w*(y)])

#ifdef __BIG_ENDIAN__
#		define RED(x)		(((x)>>24)&0xFF)
#		define GREEN(x)	(((x)>>16)&0xFF)
#		define BLUE(x)	(((x)>> 8)&0xFF)
#else
#		define RED(x)		(((x)>> 0)&0xFF)
#		define GREEN(x)	(((x)>> 8)&0xFF)
#		define BLUE(x)	(((x)>>16)&0xFF)
#endif

class ResManager;
class Level;

typedef unsigned int pixel_t;

const long double MIN_DT = 1.0/120.0;

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
	void displayForPick(int, int);
	void idle();
	void keyboard(unsigned char, int, int);
	void setupInterface(void(*cb)(int i));
	void glui_callBack( int id );

	static void clear(){
		delete inst; inst = NULL;
	}
	ResManager * resman;
private:
	Game(void);
	static Game* inst;

	Level * level;
	
	IJTime t_init;
	IJTime t_delta;
	componentVector components;

	int WIN_WIDTH, WIN_HEIGHT;
	int main_window;
	GLUI *glui;
	std::string fps_text;
	GLUI_EditText *fps_gauge;

	//glui interface variables
	float   transX;
	float   transY;
	float   transZ;
	float   rotX;
	float   rotY;
	float   camEyeX;
	float   camEyeY;
	float   camEyeZ;
	float   camLookAtX;
	float   camLookAtY;
	float   camLookAtZ;
	int     cameraProfile;
	int     picking;
};

#endif