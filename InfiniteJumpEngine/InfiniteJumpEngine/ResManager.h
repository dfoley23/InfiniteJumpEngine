#ifndef RESMANAGER_H
#define RESMANAGER_H
#include "Level.h"
#include "Game.h"
#include "glIncludes.h"

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level *getTriangleLevel();
	Level *getGolfLevel();
};

#endif