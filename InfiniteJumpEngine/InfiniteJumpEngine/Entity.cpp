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

void Entity::draw ( MeshBatch * batch ){
	for (componentIter c = components.begin(); c != components.end(); c++){
		(*c)->draw(batch);
	}
}

glm::mat4 Entity::transform(glm::mat4 in){
	if (parent){
		in = parent->transform(in);
	}
	if (tform){
		in = tform->transform(in);
	}
	return in;
}


// Accessor methods
//  


// Other methods
//  

void Entity::initAttributes ( ) {
	tform = NULL;
}

