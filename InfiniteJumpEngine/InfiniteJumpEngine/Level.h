

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

#include "Entity.h"
#include "Camera.h"
#include "MeshBatch.h"
#include "Ball.h"
using namespace std;
/**
* class Level
* 
*/

typedef std::vector<Entity*>::iterator entityIter;

class Level
{
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	Level ( );

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

	MeshBatch * pickBatch;

	Ball * ball;

	vector<Entity *> getEntities( );

private:
	
	vector<Entity*> entities;


};

#endif //LEVEL_H
