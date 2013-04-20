#include "Level.h"

// Constructors/Destructors
//  

Level::Level ( ) {
	camera = new Camera( ); 
}

Level::~Level ( ) { 
	clear();
}

//  
// Methods
//  
void Level::update(float dT){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->update( dT );
	}
}


void Level::draw( ){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->draw( camera );
	}
}

void Level::clear( ){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		delete (*it);
	}
}
// Accessor methods
//  


// Other methods
//  