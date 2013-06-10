#include "Ball.h"

Ball::Ball ( glm::vec3 pos, glm::vec3 color, TileSet * tiles, int tileId ):
forward(glm::vec3(0,0,-5), 0.07f, true)
	,back(glm::vec3(0,0,5), 0.07f, true)
	,left(glm::vec3(-5,0,0), 0.07f, true)
	,right(glm::vec3(5,0,0), 0.07f, true)
{
	tileSet = tiles;
	currentTile = tileSet->getTile( tileId-1 );
	currentTile->getMesh()->changeColor( 0.0, 1, 1 );
	mesh = generateMesh( );
	mesh->setDynamic( 1 );
	radius = (mesh->getMaxPoint().x - mesh->getMinPoint().x ) /2.0f;
	rotation = 0.0f;
	physComp = new PhysicsComponent();
	physComp->setParent(this);
	mesh->setParent(physComp);
	physComp->getKinematics()->loc.setPosition( pos.x+radius, pos.y+radius, pos.z+radius );
	mesh->setCenter( physComp->getKinematics()->loc.getPosition() );
	RayCollider * intersect = new RayCollider( );
	intersect->setParent(physComp);
	physComp->setMainCollider( intersect );
	physComp->addForce(&forward);
	physComp->addForce(&back);
	physComp->addForce(&left);
	physComp->addForce(&right);
	physComp->addForce(&rolling);
	rolling.start();
	for ( int i=0; i<static_cast<int>(tiles->tiles.size()); i++ ) {
		vector<PlaneCollider*> edgeColliders = tiles->tiles.at(i)->getEdgeColliders();
		for ( int j=0; j<static_cast<int>(edgeColliders.size()); j++ ) {
			physComp->addCollider( edgeColliders.at(j) );
		}
	}
}

Ball::~Ball ( ) {
	delete physComp;
	deleteMesh();
}

void Ball::update( float dT ) {
	try {
		luabind::call_function<int>(this->lua->getState(), this->scriptFile.c_str(), 0);
	} catch (luabind::error &e){
		cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
	}
	glm::vec3 velocity = physComp->getKinematics()->vel.getPosition();

	if ( glm::length( velocity ) > 0 ) {
		glm::vec3 rotAxis = glm::cross( velocity, glm::vec3( 0, 1, 0 ) );
		rotation -= dT * ( 16.f * (float)IJ_PI );
		sendMessage(physComp->getKinematics(), NULL, "rotate", glm::vec4(rotAxis.x, rotAxis.y, rotAxis.z, rotation));
	}

	glm::vec3 tN = glm::normalize(currentTile->getNormal());
	glm::vec3 t_xAxis = glm::cross( tN, glm::vec3(0, 1, 0) );
	//rolling force direction
	glm::vec3 tR = glm::cross( tN, t_xAxis ) * glm::dot( tN, glm::vec3( 0, 1, 0 ) );

	rolling.setVector( tR );

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
	mesh->setCenter( physComp->getKinematics()->loc.getPosition() );
}

void Ball::setUsingScript( string script, LuaBaseComponent * luaBase ) {
	this->scriptFile = script;
	lua = luaBase;
}

void Ball::draw( MeshBatch * batch ) {
	getMesh()->draw(batch);
}

void Ball::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	getMesh()->drawForPick(batch, pickColors);
}

/*
* reset the data you want to check collision with 
* use the current tiles walls and all colliders from neighbors
* and neighbors of neighbors
*/
void Ball::resetCollisionData( ) {
	physComp->collisionData.clear();
	map<int, int> usedNeighbors;
	usedNeighbors.insert( pair<int, int>(currentTile->getTileId(), currentTile->getTileId()) );
	//insert the cups collision data
	for ( int i=0; i< currentTile->getNeighborCount(); i++ ) {
		if ( currentTile->getNeighbor( i ) == Tile::NO_NEIGHBOR ) {
			physComp->collisionData.push_back( currentTile->getEdgeColliders().at( i ) );
		} else {
			physComp->collisionData.push_back( currentTile->getEdgeColliders().at( i ) );
			//push back first neighbors data
			Tile * neighbor = tileSet->getTile( currentTile->getNeighbor( i )-1 );
			physComp->collisionData.insert( physComp->collisionData.end(), 
				neighbor->edgeColliders.begin(), neighbor->edgeColliders.end() );
			//this neighbor has been used
			usedNeighbors.insert( pair<int, int>(neighbor->getTileId(), neighbor->getTileId()) );
			//neighbors of this neighbor
			for ( int j=0; j< neighbor->getNeighborCount(); j++ ) {
				if ( neighbor->getNeighbor( j ) != Tile::NO_NEIGHBOR ) {
					Tile * neighbor2 = tileSet->getTile( neighbor->getNeighbor( j )-1 );
					//if this neighbor has not been used
					if ( usedNeighbors.find( neighbor2->getTileId() ) == usedNeighbors.end() ) {
						physComp->collisionData.insert( physComp->collisionData.end(), 
							neighbor2->edgeColliders.begin(), neighbor2->edgeColliders.end() );
						usedNeighbors.insert( pair<int, int>(neighbor2->getTileId(), neighbor2->getTileId()) );
					}
				} 
			}
		}
	}
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

glm::vec3 Ball::getPos( ) {
	return physComp->getKinematics()->loc.getPosition();
}

glm::vec3 Ball::getVel( ) {
	return	physComp->getKinematics()->vel.getPosition();
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
	} else if (!message->getContent().compare("shoot")){
		glm::vec3 tN = glm::normalize(currentTile->getNormal());
		glm::vec3 t_xAxis = glm::cross( tN, glm::vec3(0, 1, 0) );
		//rolling force direction
		glm::vec3 tR = glm::cross( tN, t_xAxis );
		glm::vec3 xZ_dir = message->getVector().xyz;
		//xaxis to direction
		glm::vec3 dir_xAxis = glm::normalize(glm::cross( xZ_dir, glm::vec3(0, 1, 0 ) ));

		//balls new direction
		glm::vec3 new_dir = glm::normalize(glm::cross( tN, dir_xAxis )) * glm::length( xZ_dir );
		physComp->getKinematics()->acc.setPosition( glm::vec3( 0, 0, 0 ) );
		physComp->getKinematics()->vel.setPosition( new_dir );

		//physComp->getKinematics()->vel.setPosition( message->getVector().xyz );
	} else if (!message->getContent().compare("InterSection")){
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

			reflect = true;
		} else {
			Tile * tile = (Tile*)plane->getParent();
			currentTile->getMesh()->changeColor( 0, 0.7f, 0 );
			this->currentTile = tile;
			//reset the collision data based on the current tile
			resetCollisionData( );
			cout << currentTile->getTileId() << endl;
			currentTile->getMesh()->changeColor( 0.0, 1, 1 );
			glm::vec3 tN = glm::normalize(tile->getNormal());
			glm::vec3 t_xAxis = glm::cross( tN, glm::vec3(0, 1, 0) );
			//rolling force direction
			glm::vec3 tR = glm::cross( tN, t_xAxis );
			//xaxis to direction
			glm::vec3 dir_xAxis = glm::normalize(glm::cross( xZ_dir, glm::vec3(0, 1, 0 ) ));

			//balls new direction
			glm::vec3 new_dir = glm::normalize(glm::cross( tN, dir_xAxis )) * glm::length( xZ_dir );
			physComp->getKinematics()->acc.setPosition( glm::vec3( 0, 0, 0 ) );
			physComp->getKinematics()->vel.setPosition( new_dir );

		}
	} else if (parent) {
		sendMessage(message, parent);
	}
}
