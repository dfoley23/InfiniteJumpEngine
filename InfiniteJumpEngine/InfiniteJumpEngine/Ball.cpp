#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ) {
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->max.x - mesh->min.x ) /2.0f;
	physComp = new PhysicsComponent();
	physComp->setParent(this);
	mesh->setParent(physComp);
	PointCollider * pCollide = new PointCollider( getMesh()->center );
	pCollide->setParent( this );
	physComp->setMainCollider(pCollide);
	physComp->getKinematics()->loc.setPosition( pos.x+radius, pos.y+radius, pos.z+radius );
	mesh->center = physComp->getKinematics()->loc.getPosition();
}

Ball::~Ball ( ) {
	deleteMesh();
}


void Ball::applyImpulse( glm::vec3 impulse ) {
	physComp->getKinematics()->applyImpulse( impulse );
}

void Ball::update( float dT ) {
	physComp->update( dT );
	mesh->center = physComp->getKinematics()->loc.getPosition();
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
