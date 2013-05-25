
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
void Camera::update (glm::vec3 pos, glm::vec3 dir){
	//updates camera based on it current profile
	glm::vec3 scaleDir = glm::normalize( dir ) * 0.25f;
	camDir = camLookAt*10.f - camEye*10.f;
	switch( cameraProfile ) {
	case 0: //third person
		camEye = glm::vec3( pos.x-scaleDir.x, pos.y + 0.2f, pos.z - scaleDir.z);
		camLookAt = glm::vec3( pos.x, pos.y+0.1f, pos.z);
		camUp = glm::vec3( 0, 1, 0 );
		camDir = camLookAt*10.f - camEye*10.f;
		break;
	case 1: //first person
		camEye = glm::vec3( pos.x,pos.y+0.1f,pos.z);
		camLookAt = glm::vec3( pos.x+scaleDir.x, pos.y+0.01f,pos.z+scaleDir.z );
		camUp = glm::vec3( 0, 1, 0 );
		camDir = camLookAt*10.f - camEye*10.f;
		break;
	case 2: //top down
		camEye = glm::vec3( pos.x, 
			pos.y+6.0f,
			pos.z );
		camLookAt = pos;
		camUp = glm::vec3( 0, 0, -1 );
		camDir = camUp;
		break;
	default:
		break;
	}
	//sets the current camera transformation matrix
	cam = glm::lookAt( camEye, camLookAt, camUp );
}

/**
* switches the current camera profile
*/
void Camera::switchProfile( int profile ) {
	cameraProfile = profile;
}

glm::vec3 Camera::getDir( ) {
	return camDir;
}

// Accessor methods
//  


// Other methods
//  

void Camera::initAttributes ( ) {
	camEye = glm::vec3( 0, 4, 6 );
	camLookAt = glm::vec3( 0, 0, 0 );
	camUp = glm::vec3( 0, 1, 0 );
	camDir = glm::vec3( 0, 0, -1 );
}
