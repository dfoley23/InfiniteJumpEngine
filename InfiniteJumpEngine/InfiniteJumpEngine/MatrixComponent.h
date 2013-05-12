#ifndef MATRIX_COMPONENT_H
#define MATRIX_COMPONENT_H
#pragma once
#include "glIncludes.h"
#include "TransformComponent.h"

class MatrixComponent :
	public TransformComponent
{
public:
	MatrixComponent(void);
	~MatrixComponent(void);
	void setMatrix(glm::mat4 m){matrix = m;}
	glm::mat4 getTransformation(){return matrix;};
protected:
	glm::mat4 matrix;
};

#endif