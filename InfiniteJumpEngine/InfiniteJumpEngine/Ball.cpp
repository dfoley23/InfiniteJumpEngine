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

void Ball::update( float dT ) {
	pCollider->point = getMesh()->center;
	bool isCollided = false;
	Tile * checkTile = currentTile;
	BoxCollider * tileCollider = new BoxCollider();
	glm::vec3 pos;
	glm::vec3 dim;
	//TODO make this only test neighbors in the direction of the ball
	int recurseNeighbor = 0;
	while ( !isCollided && recurseNeighbor < currentTile->getNeighborCount() ) {
		pos = glm::vec3 ( checkTile->getMesh()->min.x, -100, checkTile->getMesh()->min.z );
		dim = glm::vec3 ( checkTile->getMesh()->max.x, 100, checkTile->getMesh()->max.z );
		tileCollider->setPos( pos );
		tileCollider->setDim( dim );
		isCollided = pCollider->isColliding( tileCollider );
		if ( !isCollided ) {
			for ( int i=0; i < checkTile->getNeighborCount(); i++ ) {
				//TODO make this only test neighbors in the direction of the ball
				int neighbor = checkTile->getNeighbor( i );
				if ( neighbor != Tile::NO_NEIGHBOR && neighbor != currentTile->getTileId() ) {
					pos = glm::vec3 ( tileSet->getTile( neighbor )->getMesh()->min.x, 
						-100, 
						tileSet->getTile( neighbor )->getMesh()->min.z );
					dim = glm::vec3 ( tileSet->getTile( neighbor )->getMesh()->max.x, 
						100, 
						tileSet->getTile( neighbor )->getMesh()->max.z );
					tileCollider->setPos( pos );
					tileCollider->setDim( dim );
					isCollided = pCollider->isColliding( tileCollider );
					if ( isCollided ) {
						checkTile = tileSet->getTile( neighbor );
						cout << "the ball switched tiles and is now on tile number: " << neighbor << endl;
						break;
					}
				}
			}
		} else {	
			//cout << "the ball hit the currenttile which is tile number: " << checkTile->getTileId() << endl;
		}
		//if no collision on any of the current tiles neighbors
		//check neighbors of the next tile
		if ( !isCollided ) {
			int neighbor = currentTile->getNeighbor( recurseNeighbor );
			while ( ( neighbor == Tile::NO_NEIGHBOR || neighbor == currentTile->getTileId() ) && recurseNeighbor < currentTile->getNeighborCount() ) {
				recurseNeighbor++;
				neighbor = currentTile->getNeighbor( recurseNeighbor );
			}
			if ( recurseNeighbor < currentTile->getNeighborCount() ) {
				checkTile = tileSet->getTile( neighbor );
				recurseNeighbor++;
			}
		}
	}
	if ( !isCollided ) {
		cout << "your ball is not on a tile" << endl;
	} else {
		currentTile = checkTile;
	}
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