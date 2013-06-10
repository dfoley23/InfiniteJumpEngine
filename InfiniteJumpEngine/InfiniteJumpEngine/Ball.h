#pragma once
#ifndef BALL_H
#define BALL_H

#include <string>
#include "Component.h"
#include "Mesh.h"
#include "PhysicsComponent.h"

class Tile;
class TileSet;

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
	void setUsingScript( string scriptFile, LuaBaseComponent * luaBase );
	void deleteMesh();
	void update( float dT );
	void draw(MeshBatch * batch);
	void drawForPick(MeshBatch * batch, glm::vec3 pickColors);
	void hitTile( Tile * tile );
	void receiveMessage( IJMessage* message );
	void resetCollisionData( );
	glm::vec3 getVel( );
	glm::vec3 getPos( );
	PhysicsComponent *getPhysics();
private:
	PhysicsComponent * physComp;
	Mesh * mesh;
	TileSet * tileSet;
	Tile * currentTile;
	string scriptFile;
	LuaBaseComponent * lua;
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