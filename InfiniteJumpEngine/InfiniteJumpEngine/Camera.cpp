
#include "Camera.h"

// Constructors/Destructors
//  
Camera::Camera ( ) {
	initAttributes();
}

Camera::~Camera ( ) { 

}

//  
// Methods
//  
void Camera::update (glm::vec3 pos){
	switch( cameraProfile ) {
		case 0: //third person
			cam = glm::lookAt( glm::vec3(  pos.x, 
				pos.y + 0.25f,
				pos.z + 0.25f ),
				pos, glm::vec3( 0, 1, 0 ) );
			break;
		case 1: //first person
			cam = glm::lookAt( glm::vec3( pos.x, 
				pos.y,
				pos.z-0.05f ),
				glm::vec3( pos.x, 
				pos.y,
				pos.z-1.0f ), glm::vec3( 0, 1, 0 ) );
			break;
		case 2: //top down
			cam = glm::lookAt( glm::vec3( pos.x, 
				pos.y+6.0f,
				pos.z ),
				pos, glm::vec3( 0, 0, 1 ) );
			break;
		default:
			break;
		}
}

void Camera::switchProfile( int profile ) {
	cameraProfile = profile;
}

// Accessor methods
//  


// Other methods
//  

void Camera::initAttributes ( ) {

}
