
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
void Camera::update (){
	if ( usingScript ) {
		try {
			luabind::call_function<int>(this->lua->getState(), "updateCamera", 0);
		} catch (luabind::error &e){
			cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
		}
	}
	//sets the current camera transformation matrix
	cam = glm::lookAt( camEye, camLookAt, camUp );
}

void Camera::setUsingScript( string scriptFile, LuaBaseComponent * luaBase ) {
	usingScript = true;
	updateScript = scriptFile;
	lua = luaBase;
}

void Camera::changeLightPos( float x, float y, float z ) {
	lightPos = glm::vec3( x, y, z );
}

void Camera::changeEyePos( float x, float y, float z ){
	camEye = glm::vec3( x, y, z );
}

glm::vec3 Camera::getEyePos(){
	return camEye;
}

glm::vec3 Camera::getLookAtPos(){
	return camLookAt;
}

void Camera::changeUpDir( float x, float y, float z ) {
	camUp = glm::vec3( x, y, z );
}


void Camera::changeLookAtPos( float x, float y, float z ){
	camLookAt = glm::vec3( x, y, z );
}

// Accessor methods
//  


// Other methods
//  

void Camera::initAttributes ( ) {
	usingScript = false;
	updateScript = "";
	camEye = glm::vec3( 0, 4, 6 );
	camLookAt = glm::vec3( 0, 0, 0 );
	camUp = glm::vec3( 0, 1, 0 );
	camDir = glm::vec3( 0, 0, -1 );
	cam = glm::lookAt( camEye, camLookAt, camUp );
}
