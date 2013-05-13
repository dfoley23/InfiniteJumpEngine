#pragma once
#include "Collider.h"
#include "TileSet.h"

class TileSetCollider :
	public Collider
{
public:
	TileSetCollider(TileSet*);
	~TileSetCollider(void);
protected:
	TileSet* tileset;
};

