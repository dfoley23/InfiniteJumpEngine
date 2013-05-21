#pragma once
#ifndef CUP_H
#define CUP_H

#include "Component.h"
#include "glIncludes.h"
#include "Game.h"
#include "Mesh.h"
#include "PlaneCollider.h"

using namespace std;
/**
* class CUP_H
*
*/

class Cup: public Component
{
public:	
    // Constructors/Destructors
    //
	virtual ~Cup ( );
	Cup ( glm::vec3 pos );
	Mesh *getMesh();
	Mesh *generateMesh();
	void deleteMesh();
	void draw(MeshBatch * batch);
	void drawForPick(MeshBatch * batch, glm::vec3 pickColors);
	void receiveMessage( IJMessage* message );
	vector<PlaneCollider*> edgeColliders;
private:
	void buildMesh( );
protected:
	Mesh * mesh;
	vector<glm::vec3>verts;
	glm::vec3 pos;
};

#endif CUP_H