#ifndef BALL_H
#define BALL_H

#include <string>
#include "glIncludes.h"
#include "Mesh.h"
#include "Tile.h"
#include "ResManager.h"
#include "Game.h"
using namespace std;
/**
* class Tile
*
*/

class Ball: public Component
{
public:	
    // Constructors/Destructors
    //
	virtual ~Ball ( );
	Ball ( glm::vec3 pos, glm::vec3 color);
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
	void draw(MeshBatch * batch);
	void drawForPick(MeshBatch * batch, glm::vec3 pickColors);
private:
	Mesh * mesh;
	Tile * currentTile;
	float radius;
	void buildMesh( );
protected:
};

#endif // BALL_H