#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ):
	forward(glm::vec3(0,0,-5), 0.1f, true)
	,back(glm::vec3(0,0,5), 0.1f, true)
	,left(glm::vec3(-5,0,0), 0.1f, true)
	,right(glm::vec3(5,0,0), 0.1f, true)
{
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->max.x - mesh->min.x ) /2.0f;
	physComp = new PhysicsComponent();
	physComp->setParent(this);
	mesh->setParent(physComp);
	physComp->getKinematics()->loc.setPosition( pos.x+radius, pos.y+radius, pos.z+radius );
	mesh->center = physComp->getKinematics()->loc.getPosition();
	InterSectionCollider * intersect = new InterSectionCollider( );
	intersect->setParent(physComp);
	physComp->setMainCollider( intersect );
	physComp->addForce(&forward);
	physComp->addForce(&back);
	physComp->addForce(&left);
	physComp->addForce(&right);
}

Ball::~Ball ( ) {
	deleteMesh();
}


void Ball::applyImpulse( glm::vec3 impulse ) {
	physComp->getKinematics()->applyImpulse( impulse );
}

void Ball::update( float dT ) {
	InterSectionCollider* ballRay = (InterSectionCollider*)physComp->getMainCollider();
	ballRay->setRayStart( mesh->getCenter() );
	ballRay->setDirection( physComp->getKinematics()->vel.getPosition() );
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

void Ball::receiveMessage( IJMessage* message ){
	if (!message->getContent().compare("forward")){
		cout<< "ball moving forward" << endl;
		forward.start();
	} else if (!message->getContent().compare("back")){
		cout<< "ball moving back" << endl;
		back.start();
	} else if (!message->getContent().compare("left")){
		cout<< "ball moving left" << endl;
		left.start();
	} else if (!message->getContent().compare("right")){
		cout<< "ball moving right" << endl;
		right.start();
	} else if (!message->getContent().compare("tileCollision")){
		this->currentTile = (Tile*)message->getOther()->getParent();
		cout << "you are rolling on tile number: " << currentTile->getTileId() << endl;
	} else if (parent) {
		sendMessage(message, parent);
	}
}
