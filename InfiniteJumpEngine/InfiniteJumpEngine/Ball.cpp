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
	RayCollider * intersect = new RayCollider( );
	intersect->setParent(physComp);
	physComp->setMainCollider( intersect );
	physComp->addForce(&forward);
	physComp->addForce(&back);
	physComp->addForce(&left);
	physComp->addForce(&right);
	MeshCollider * meshCollide;
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
	RayCollider* ballRay = (RayCollider*)physComp->getMainCollider();
	physComp->pointCollider->point = mesh->getCenter();
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
	} else if (!message->getContent().compare("InterSection")){
		//cout << "you are rolling on tile number: " << currentTile->getTileId() << endl;
		PlaneCollider * plane = (PlaneCollider*)message->getOther();

		//balls current direction
		glm::vec3 xZ_dir = physComp->getKinematics()->vel.getPosition();
		if ( plane->isSolidPlane() ) {
			glm::vec3 pN = glm::normalize(plane->getNormal());
			glm::vec3 projDir = pN * glm::dot( pN, xZ_dir );
			//reflect direction
			glm::vec3 reflect_dir = 2.f * projDir + xZ_dir;
			
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
		cout << "collider address: " << message->getOther() << endl;
	} else if ( !message->getContent().compare("MeshCollision") ){
		Tile * tile = (Tile*)message->getOther()->getParent();
		this->currentTile = tile;
		cout << tile->getTileId() << endl;
	} else if (parent) {
		sendMessage(message, parent);
	}
}
