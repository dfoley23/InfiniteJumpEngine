#include "Game.h"


Game::Game(void)
{
	WIN_WIDTH = 1280;
	WIN_HEIGHT = 720;
}


Game::~Game(void)
{
	for (componentIter c = components.begin(); c != components.end(); c++){
		delete (*c);
	}
}
