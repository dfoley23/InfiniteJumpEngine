#ifndef RESMANAGER_H
#define RESMANAGER_H

#include <sstream>

#include "Tile.h"
#include "Ball.h"
#include "Entity.h"
#include "Level.h"

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level * getTriangleLevel(string filename);
	Mesh *readObjFile(string filename);

private:
};

#endif RESMANAGER_H