#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "IJTime.h"
#include "IJMessage.h"
#include "Component.h"
#include "glIncludes.h"
#include "luaIncludes.h"
#include "ResManager.h"
#include "ScoresComponent.h"
#include "LuaBaseComponent.h"

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
	//Move to an InputComponent?
	void mouse_click(int, int, int, int);
	void mouse_drag(int, int );
	void mouse_wheel( int wheel, int direction, int x, int y );
	void keyboard(unsigned char, int, int);
	void special_keyboard(int key, int x, int y);
	void setupInterface(void(*cb)(int i));
	void setupHighScoreScreen( );
	void glui_callBack( int id );
	void switchLevel( );
	void exposeClassesToLua( );
	LuaBaseComponent * getLuaBase( );

	static void clear(){
		delete inst; inst = NULL;
	}
	ResManager * resman;
	//Move to a GUI component
	GLUI_StaticText * courseName;
	GLUI_StaticText * holeName;
	GLUI_StaticText * holePar;
	GLUI_StaticText * holeScore;
	GLUI_StaticText * totalScore;
	GLUI_StaticText * highScores;
	GLUI_Panel * mainPanel;
	//Move to Minigolf Script
	int totalPar;
	int curPar;
	int curScore;
	int holeStrokeCount;
	ScoresComponent scores;
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

	string  levelID;
	int     sub_levelID;

	glm::vec3 clickPoint;
	bool hasPressed;
	int totalStrokeCount;

	int scaleDir;

	LuaBaseComponent *lua;
};

#endif GAME_H