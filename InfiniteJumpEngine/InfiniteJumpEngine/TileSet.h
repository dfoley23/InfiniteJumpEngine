#pragma once
#include <vector>
#include "Tile.h"
#include "Mesh.h"
using std::vector;

class TileSet: public EntityComponent
{
public:
TileSet(void);
virtual ~TileSet(void);

Mesh *createMesh();
Mesh *getMesh(){return mesh;}
void clearMesh(){delete mesh; mesh = NULL;}
void update(float);
void draw( Camera * );

protected:
vector<Tile*> tiles;
Mesh *mesh;
};