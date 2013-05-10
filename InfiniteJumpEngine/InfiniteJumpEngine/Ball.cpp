#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ) {
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->max.x - mesh->min.x ) /2.0f;
	mesh->translate( pos.x+radius, pos.y+radius, pos.z+radius );
	pCollider = new PointCollider( getMesh()->center );
	kinematics = new KinematicComponent( );
}

Ball::~Ball ( ) {
	deleteMesh();
}


void Ball::applyImpulse( glm::vec3 impulse ) {
	kinematics->applyImpulse( impulse );
}

void Ball::update( float dT ) {

	//kinematics->update( dT );
}

void Ball::draw( MeshBatch * batch ) {
	getMesh()->draw(batch);
}

void Ball::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	getMesh()->drawForPick(batch, pickColors);
}

void Ball::deleteMesh(){
	if (mesh){
		delete mesh; mesh = NULL;
	}
}

Mesh* Ball::getMesh(){
	if (!mesh){ mesh = generateMesh();}
	return mesh;
}

Mesh* Ball::generateMesh(){
	return Game::game()->resman->readObjFile( "ballobj.obj" );
}