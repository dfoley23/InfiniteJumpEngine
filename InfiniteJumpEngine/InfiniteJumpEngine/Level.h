#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

#include "Entity.h"
#include "Camera.h"
#include "MeshBatch.h"
#include "MatrixComponent.h"
using namespace std;
/**
* class Level
* 
*/
class Ball;


typedef std::vector<Entity*>::iterator entityIter;

class Level
{
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	Level ( string name );

	/**
	* Empty Destructor
	*/
	virtual ~Level ( );

	Camera * camera;

	void update(float);

	void draw( );

	void drawForPick( );

	void clear( );

	void addEntity( Entity * entity );

	Mesh * pickedMesh;

	MeshBatch * meshBatch;

	MeshBatch * hudBatch;

	MeshBatch * pickBatch;

	Ball * ball;

	vector<Entity *> getEntities( );

	int maxSubLevels;

private:
	
	vector<Entity*> entities;

	vector<Entity*> hudEntities;

	MatrixComponent * hudView;

	string name;

};

#endif LEVEL_H
