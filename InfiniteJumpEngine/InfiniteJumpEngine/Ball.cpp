#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ) {
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->max.x - mesh->min.x ) /2.0f;
	mesh->translate( pos.x+radius, pos.y+radius, pos.z+radius );
	physComp = new PhysicsComponent();
	physComp->setParent(this);
	mesh->setParent(physComp);
	PointCollider * pCollide = new PointCollider( getMesh()->center );
	pCollide->setParent( this );
	physComp->setMainCollider(pCollide);
}

Ball::~Ball ( ) {
	deleteMesh();
}


void Ball::applyImpulse( glm::vec3 impulse ) {
	physComp->getKinematics()->applyImpulse( impulse );
}

void Ball::update( float dT ) {
	physComp->update( dT );
	//kinematics->update( dT );
}

void Ball::draw( MeshBatch * batch ) {
	getMesh()->draw(batch);
}

void Ball::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	getMesh()->drawForPick(batch, pickColors);
}

PhysicsComponent * Ball::getPhysics(){
	return physComp;
}

void Ball::addCollisionObject( Collider * collider ){ 
	physComp->addCollider( collider );
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

void Ball::receiveMessage( IJMessage message ){
	
}
