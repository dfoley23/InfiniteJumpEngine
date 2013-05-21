#ifndef TILE_H
#define TILE_H

#include "Component.h"
#include "glIncludes.h"
#include "PlaneCollider.h"
#include "Mesh.h"

class TileSet;

using namespace std;
/**
* class Tile
*
*/

class Tile: public Component
{
public:	
	friend class TileSet;
    // Constructors/Destructors
    //
	virtual ~Tile ( );
	Tile ( int, vector<glm::vec3>, vector<int>, glm::vec3 color);
	inline bool hasNeighbor(unsigned int e){return neighbors[e] != NO_NEIGHBOR;}
	int findNeighbor(unsigned int id);
	int getNeighbor(unsigned int e);
	int getNeighborCount();
	static const int NO_NEIGHBOR = 0;
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
	void draw(MeshBatch * batch);
	void drawForPick(MeshBatch * batch, glm::vec3 pickColors);
	int getTileId( );
	glm::vec3 getNormal();
	vector<PlaneCollider*> getEdgeColliders();
	vector<Mesh *> edges;
	vector<PlaneCollider*> edgeColliders;
private:
	void buildMesh( );
protected:
	Mesh * mesh;
	glm::vec3 normal;
	unsigned int id;
	vector<glm::vec3>verts;
	vector<int> neighbors;
	glm::vec3 color;
	glm::vec3 wall_color;
};

#endif TILE_H