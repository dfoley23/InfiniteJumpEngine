#include "TileSet.h"


TileSet::TileSet(void)
{
}


TileSet::~TileSet(void)
{
}

void TileSet::update(float dT){
	for (tileIter t = tiles.begin(); t != tiles.end(); t++){
		t->second->update(dT);
	}
}

void TileSet::draw( MeshBatch * batch ){
	for (tileIter t = tiles.begin(); t != tiles.end(); t++){
		t->second->draw(batch);
	}
}

void TileSet::drawForPick( MeshBatch * batch, glm::vec3 pickColors ){
	for (tileIter t = tiles.begin(); t != tiles.end(); t++){
		t->second->drawForPick(batch, pickColors);
	}
}

void TileSet::addTile( int key, Tile * tile ) {
	this->tiles[key] = tile;
}

Tile * TileSet::getTile( int key ) {
	return tiles[key];
}
