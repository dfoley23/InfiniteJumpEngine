#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ):
forward(glm::vec3(0,0,-5), 0.07f, true)
	,back(glm::vec3(0,0,5), 0.07f, true)
	,left(glm::vec3(-5,0,0), 0.07f, true)
	,right(glm::vec3(5,0,0), 0.07f, true)
{
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->max.x - mesh->min.x ) /2.0f;
	rotation = 0.0f;
	physComp = new PhysicsComponent();
	physComp->setParent(this);
	mesh->setParent(physComp);
	physComp->getKinematics()->loc.setPosition( pos.x+radius, pos.y+radius, pos.z+radius );
	mesh->center = physComp->getKinematics()->loc.getPosition();
	RayCollider * intersect = new RayCollider( );
	intersect->setParent(physComp);
	physComp->setMainCollider( intersect );
	physComp->addForce(&forward);
	physComp->addForce(&back);
	physComp->addForce(&left);
	physComp->addForce(&right);
	PointCollider * pCollide = new PointCollider( mesh->center );
	pCollide->setParent( this );
	physComp->pointCollider = pCollide;
	for ( int i=0; i<static_cast<int>(tiles->tiles.size()); i++ ) {
		MeshCollider * meshC = new MeshCollider( tiles->tiles.at(i)->getMesh() );
		meshC->setParent( tiles->tiles.at( i ) ) ;
		physComp->meshCollision.push_back( meshC );
		vector<PlaneCollider*> edgeColliders = tiles->tiles.at(i)->getEdgeColliders();
		for ( int j=0; j<static_cast<int>(edgeColliders.size()); j++ ) {
			physComp->addCollider( edgeColliders.at(j) );
		}
	}
}

Ball::~Ball ( ) {
	deleteMesh();
}

void Ball::update( float dT ) {
	glm::vec3 velocity = physComp->getKinematics()->vel.getPosition();
	RayCollider* ballRay = (RayCollider*)physComp->getMainCollider();
	ballRay->setRayStart( mesh->getCenter() );
	ballRay->setDirection( velocity );

	/*if ( glm::length( velocity ) > 0 ) {
		glm::vec3 rotAxis = glm::cross( velocity, glm::vec3( 0, 1, 0 ) );
		rotation += dT * ( 4 * IJ_PI );
		getMesh()->rotate( rotation, rotAxis );
	}*/
	/*physComp->collisionData.clear();
	for ( int i=0; i< currentTile->getNeighborCount(); i++ ) {
		if ( currentTile->getNeighbor( i ) == Tile::NO_NEIGHBOR ) {
			physComp->collisionData.push_back( currentTile->edgeColliders.at( i ) );
		} else {
			Tile * neighbor = tileSet->getTile( currentTile->getNeighbor( i ) );
			physComp->collisionData.insert( physComp->collisionData.end(), 
				neighbor->edgeColliders.begin(), neighbor->edgeColliders.end() );
		}
	}*/
	physComp->update( dT );
	float minYPos = currentTile->getMesh()->getMinPoint().y+radius;
	float maxYPos = currentTile->getMesh()->getMaxPoint().y+radius;
	glm::vec3 curPos = physComp->getKinematics()->loc.getPosition();
	if ( minYPos > curPos.y ) {
		glm::vec3 newPos = glm::vec3( curPos.x, minYPos, curPos.z );
		physComp->getKinematics()->loc.setPosition( newPos );
	} else if ( maxYPos < curPos.y ) {
		glm::vec3 newPos = glm::vec3( curPos.x, maxYPos, curPos.z );
		physComp->getKinematics()->loc.setPosition( newPos );
	}
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
	} else if (!message->getContent().compare("InterSection")){
		//cout << "you are rolling on tile number: " << currentTile->getTileId() << endl;
		PlaneCollider * plane = (PlaneCollider*)message->getOther();

		//balls current direction
		glm::vec3 xZ_dir = physComp->getKinematics()->vel.getPosition();
		if ( plane->isSolidPlane() ) {
			glm::vec3 pN = glm::normalize(plane->getNormal());
			glm::vec3 projDir = pN * glm::dot( pN, -xZ_dir );
			//reflect direction
			glm::vec3 reflect_dir = projDir + ( projDir + xZ_dir );

			physComp->getKinematics()->acc.setPosition( glm::vec3( 0, 0, 0 ) );
			physComp->getKinematics()->vel.setPosition( reflect_dir );
			cout << "collided with an edge" << endl;
		} else {
			Tile * tile = (Tile*)plane->getParent();
			this->currentTile = tile;
			cout << tile->getTileId() << endl;
			glm::vec3 tN = glm::normalize(tile->getNormal());
			glm::vec3 t_xAxis = glm::cross( tN, glm::vec3(0, 1, 0) );
			//rolling force direction
			glm::vec3 tR = glm::cross( tN, t_xAxis );
			//xaxis to direction
			glm::vec3 dir_xAxis = glm::cross( xZ_dir, glm::vec3(0, 1, 0 ) );

			//balls new direction
			glm::vec3 new_dir = glm::normalize(glm::cross( tN, dir_xAxis ));
			glm::vec3 final_dir = xZ_dir * glm::dot( xZ_dir, new_dir );
			physComp->getKinematics()->acc.setPosition( glm::vec3( 0, 0, 0 ) );
			physComp->getKinematics()->vel.setPosition( new_dir );

		}
		//cout << "collider address: " << message->getOther() << endl;
	} else if ( !message->getContent().compare("MeshCollision") ){
		Tile * tile = (Tile*)message->getOther()->getParent();
		this->currentTile = tile;
		cout << tile->getTileId() << endl;
	} else if (parent) {
		sendMessage(message, parent);
	}
}
