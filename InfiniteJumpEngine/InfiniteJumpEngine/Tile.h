#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>
#include "glIncludes.h"
#include "Mesh.h"
#include "TileSet.h"
using namespace std;
/**
* class Tile
*
*/

class Tile
{
public:	
	friend class TileSet;
    // Constructors/Destructors
    //
	virtual ~Tile ( );
	inline bool hasNeighbor(int e){return neighbors[e] != NO_NEIGHBOR;}
	int findNeighbor(int id);
	int getNeighbor(int e);
	static const int NO_NEIGHBOR = -1;
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
protected:
	Tile ( int, vector<glm::vec3>, vector<int>);
	unsigned int id;
	vector<glm::vec3>verts;
	vector<int> neighbors;
	Mesh * mesh;
};

#endif // TILE_H