#pragma once
#ifndef BALL_H
#define BALL_H

#include <string>
#include "Component.h"
#include "Mesh.h"
#include "PhysicsComponent.h"
#include "Cup.h"

class Tile;
class TileSet;
class Cup;

using namespace std;
/**
* class Ball
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
	void hitTile( Tile * tile );
	void receiveMessage( IJMessage* message );
	void resetCollisionData( );

	PhysicsComponent *getPhysics();
	bool hitCup;
	Cup * cup;
private:
	PhysicsComponent * physComp;
	Mesh * mesh;
	TileSet * tileSet;
	Tile * currentTile;
	float radius;
	float rotation;
	Force forward;
	Force back;
	Force left;
	Force right;
	Force rolling;
	void buildMesh( );
	bool reflect;

protected:
};

#endif BALL_H