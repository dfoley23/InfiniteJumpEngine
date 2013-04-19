#pragma once
#include <vector>
#include "Tile.h"
using std::vector;

class TileSet
{
public:
	TileSet(void);
	virtual ~TileSet(void);
protected:
	vector<Tile*> tiles;
};

