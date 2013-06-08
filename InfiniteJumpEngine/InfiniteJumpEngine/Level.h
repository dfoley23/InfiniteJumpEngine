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

	MeshBatch * meshBatch;

	MeshBatch * hudBatch;

	Ball * ball;

	vector<Entity *> getEntities( );

	vector<Entity*> hudEntities;

	int maxSubLevels;

private:
	
	vector<Entity*> entities;

	MatrixComponent * hudView;

	string name;

};

#endif LEVEL_H
