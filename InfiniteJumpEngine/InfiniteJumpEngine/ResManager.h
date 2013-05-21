#ifndef RESMANAGER_H
#define RESMANAGER_H

#include <sstream>

#include "Tile.h"
#include "Ball.h"
#include "Cup.h"
#include "Entity.h"
#include "Level.h"
#include "loadpng.h"

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level * getTriangleLevel(string filename, int holeID);
	Mesh *readObjFile(string filename);
	void loadTexture(char * filename, int id);
private:
};

#endif RESMANAGER_H