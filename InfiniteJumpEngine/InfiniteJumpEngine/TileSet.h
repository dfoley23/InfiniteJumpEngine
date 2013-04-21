#pragma once
#include <vector>
#include "glIncludes.h"
#include "Tile.h"
#include "EntityComponent.h"
using std::vector;

class Tile;

class TileSet: EntityComponent
{
public:
TileSet(void);
virtual ~TileSet(void);

Mesh *createMesh();
Mesh *getMesh(){return mesh;}
void clearMesh(){delete mesh; mesh = NULL;}
void update(float);
void draw( Camera * );


	void addTile(unsigned int, vector<glm::vec3>, vector<unsigned int>);
protected:
	vector<Tile*> tiles;
	Mesh* mesh;
}
;
