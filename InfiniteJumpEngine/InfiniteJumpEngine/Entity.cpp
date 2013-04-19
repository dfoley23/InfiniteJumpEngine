#include "Entity.h"

// Constructors/Destructors
//  

Entity::Entity ( ) {
initAttributes();
}

Entity::~Entity ( ) { 

}

//  
// Methods
//  
void Entity::update (float dT){
	for (componentIter c = components.begin(); c != components.end(); c++){
		(*c)->update(dT);
	}
}

void Entity::draw (MeshBatch *batch){
	for (componentIter c = components.begin(); c != components.end(); c++){
		(*c)->draw(batch);
	}
}

// Accessor methods
//  


// Other methods
//  

void Entity::initAttributes ( ) {
}

