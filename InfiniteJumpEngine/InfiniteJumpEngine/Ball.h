#ifndef BALL_H
#define BALL_H

#include <string>
#include "glIncludes.h"
#include "Mesh.h"
#include "Tile.h"
#include "ResManager.h"
#include "Game.h"
#include "IJMessage.h"
#include "PhysicsComponent.h"
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
	Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId );
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
	void update( float dT );
	void draw(MeshBatch * batch);
	void drawForPick(MeshBatch * batch, glm::vec3 pickColors);
	void applyImpulse( glm::vec3 impulse );
	void hitTile( Tile * tile );
	void receiveMessage( IJMessage* message );
	void addCollisionObject( Collider * collider );

	PhysicsComponent *getPhysics();
private:
	PhysicsComponent * physComp;
	PointCollider * pCollide;
	Mesh * mesh;
	TileSet * tileSet;
	Tile * currentTile;
	float radius;
	Force forward;
	Force back;
	Force left;
	Force right;
	void buildMesh( );
protected:
};

#endif // BALL_H