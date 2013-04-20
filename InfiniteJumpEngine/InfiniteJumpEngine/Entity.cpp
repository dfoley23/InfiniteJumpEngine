#include "Entity.h"
#include "Camera.h"

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

void Entity::draw ( Camera * camera ){
	for (componentIter c = components.begin(); c != components.end(); c++){
		(*c)->draw(camera);
	}
}

// Accessor methods
//  


// Other methods
//  

void Entity::initAttributes ( ) {
}

