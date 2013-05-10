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
#include "KinematicComponent.h"
#include "PointCollider.h"
#include "Ball.h"

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level *getTriangleLevel(string filename);
	Level *getGolfLevel();
	Mesh *readObjFile(string filename);

private:
};

#endif