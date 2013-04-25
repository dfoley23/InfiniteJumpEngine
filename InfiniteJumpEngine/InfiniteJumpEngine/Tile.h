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
	static const int NO_NEIGHBOR = 0;
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
	void draw(Camera *camera){getMesh()->draw(camera);};
	Mesh * mesh;
private:
	void buildMesh( );
protected:
	unsigned int id;
	vector<glm::vec3>verts;
	vector<int> neighbors;
	glm::vec3 color;
	glm::vec3 wall_color;
};

#endif // TILE_H