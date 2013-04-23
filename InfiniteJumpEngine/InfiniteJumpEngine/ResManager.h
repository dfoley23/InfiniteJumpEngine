#ifndef RESMANAGER_H
#define RESMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Level.h"
#include "Game.h"
#include "glIncludes.h"
#include "Tile.h"

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level *getTriangleLevel(string filename);
	Level *getGolfLevel();
};

#endif