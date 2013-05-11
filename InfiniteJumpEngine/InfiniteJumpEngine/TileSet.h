#pragma once
#include <map>
#include "glIncludes.h"
#include "Tile.h"
#include "Component.h"
#include "MeshBatch.h"
using std::vector;

class Tile;

typedef vector<Tile*> tileVec;
typedef tileVec::iterator tileIter;

class TileSet: public Component
{
public:
	TileSet(void);
	virtual ~TileSet(void);

	void update(float);
	void draw( MeshBatch * );
	void drawForPick( MeshBatch *, glm::vec3 pickColors );
	void addTile(unsigned int, vector<glm::vec3>, vector<unsigned int>);
	void addTile( int key, Tile * );
	Tile * getTile( int key );
	vector<Tile *> tiles;
protected:
}
;
