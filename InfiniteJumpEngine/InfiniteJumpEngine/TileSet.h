#pragma once
#include <vector>
#include "glIncludes.h"
#include "Tile.h"
#include "Component.h"
#include "Camera.h"
using std::vector;

class Tile;

typedef vector<Tile*> tileVector;
typedef tileVector::iterator tileIter;

class TileSet: public Component
{
public:
	TileSet(void);
	virtual ~TileSet(void);

	void update(float);
	void draw( Camera * );
	void addTile(unsigned int, vector<glm::vec3>, vector<unsigned int>);
	void addTile( Tile * );
protected:
	vector<Tile*> tiles;
}
;
