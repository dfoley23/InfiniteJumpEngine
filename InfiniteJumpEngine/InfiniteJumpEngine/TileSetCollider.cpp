#include "TileSetCollider.h"


TileSetCollider::TileSetCollider(TileSet *t)
{
	setParent(t);
	tileset = t;
}


TileSetCollider::~TileSetCollider(void)
{
}
