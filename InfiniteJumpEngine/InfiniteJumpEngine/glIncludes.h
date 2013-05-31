#pragma once
#ifndef GLINCLUDES_H
#define GLINCLUDES_H

#define GLEW_STATIC
#include <GL/glew.h> //must include this before gl.h
#include <GL/freeglut.h>
#include <GL/glui.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <cmath>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define IJ_PI        3.14159265358979323846264338327950288
#define rad_to_deg   57.2957795131

inline float dotProduct( glm::vec3 u, glm::vec3 v ) {
	return glm::dot( u, v );
}

inline glm::vec3 crossProduct( glm::vec3 u, glm::vec3 v) {
	return glm::cross( u, v );
}

inline float length( float x, float y, float z ) {
	glm::vec3 u = glm::vec3( x, y, z );
	return glm::length( u );
}

inline glm::vec3 normalize( float x, float y, float z ) {
	glm::vec3 u = glm::vec3( x, y, z );
	return glm::normalize( u );
}

#endif GLINCLUDES_H