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

#endif GLINCLUDES_H