/*
 * GLDataObject.h
 *
 *
 *  Created on: Feb 21, 2012
 *      Author: ncesario
 *  Edited on : April 20, 2013
 *      By : dmfoley
 */

#ifndef GLDATAOBJECT_HPP_
#define GLDATAOBJECT_HPP_

#define CHECK_OPENGL_ERROR \
    for (GLint error = glGetError(); error; error = glGetError()) { \
                std::cout << "glError: " << error \
                          << " " << __FILE__ \
                          << " " << __LINE__ \
                          << std::endl; \
            }
#include <GL/glew.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>
#include <string>

#include "Shader.h"

using namespace std;

class GLDataObject {
public:
	virtual ~GLDataObject(){ };
	virtual void setUniform( Shader * shader ) = 0;
	virtual void *getData() = 0;
	virtual string getName() { return name; }
	virtual GLsizei getVecSize() = 0;
	virtual GLenum getType() = 0;
	virtual GLsizei getSizeInBytes()= 0;
	virtual GLenum getUsage() { return usage; }

	string name;
	GLenum usage;
};

class GLArrayBufObject : public GLDataObject {
public:
    virtual GLsizei getVecSize() { return vecSize; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(int); }

	virtual void genBuf() {
	    glGenBuffers(1, &bufID);
	    CHECK_OPENGL_ERROR
	    glBindBuffer(GL_ARRAY_BUFFER, bufID);
	    glBufferData(GL_ARRAY_BUFFER, getSizeInBytes(), getData(), usage);
	    CHECK_OPENGL_ERROR
	}

	GLsizei size, vecSize;
	GLuint bufID;
};

class GLMat4FData : public GLDataObject {
public:
	GLMat4FData(string name, GLboolean t, GLsizei num, GLfloat *d, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return (void *)data; }

	virtual GLsizei getVecSize() { return 16; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }

	GLboolean transpose;
	GLsizei size;
	GLfloat *data;
};

class GLMat3FData : public GLDataObject {
public:
	GLMat3FData(string name, GLboolean t, GLsizei num, GLfloat *d, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return (void *)data; }

	virtual GLsizei getVecSize() { return 9; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }

	GLboolean transpose;
	GLsizei size;
	GLfloat *data;
};

class GLVec1FData : public GLArrayBufObject {
public:
	GLVec1FData(string name, Shader * shader, GLsizei num, float data, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return ( void * ) &data; }

	virtual GLsizei getVecSize() { return 1; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }
	
	float data;
	GLint loc;
};

class GLVec2FData : public GLArrayBufObject {
public:
	GLVec2FData(string name, Shader * shader, GLsizei num, glm::vec2 data, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return (void *) &data; }

	virtual GLsizei getVecSize() { return 2; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }

	glm::vec2 data;
	GLint loc;
};

class GLVec3FData : public GLArrayBufObject {
public:
	GLVec3FData(string name, Shader * shader, GLsizei num, glm::vec3 data, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader);

	virtual void *getData() { return (void *)&data; }

	virtual GLsizei getVecSize() { return 3; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }

	glm::vec3 data;
	GLint loc;
};

class GLVec4FData : public GLArrayBufObject {
public:
	GLVec4FData(string name, Shader * shader, GLsizei num, glm::vec4 data, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return (void *)&data; }

	virtual GLsizei getVecSize() { return 4; }

	virtual GLenum  getType() { return GL_FLOAT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(float); }

	glm::vec4 data;
	GLint loc;
};

class GLVecIData : public GLArrayBufObject {
public:
	GLVecIData(string name, GLsizei num, GLsizei vecSize, GLint *d, GLenum usg = GL_STATIC_DRAW);

	virtual void setUniform( Shader * shader );

	virtual void *getData() { return (void *)data; }

	virtual GLsizei getVecSize() { return vecSize; }

	virtual GLenum  getType() { return GL_INT; }

	virtual GLsizei getSizeInBytes() { return getVecSize() * size * sizeof(int); }

	GLint *data;
};

#endif /* GLDATAOBJECT_H_ */
