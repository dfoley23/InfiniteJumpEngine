/*
 * GLDataObject.cpp
 *
 *  Created on: Feb 21, 2012
 *      Author: ncesario
 *  Edited on : April 20, 2013
 *      By : dmfoley
 */


#include "GLDataObject.h"

GLMat4FData::GLMat4FData(string name, GLboolean t, GLsizei num, GLfloat *d, GLenum usg) {
	this->name = name;
	transpose = t;
	size = num;
	data = d;
	usage = usg;
}

void GLMat4FData::setUniform( Shader * shader ) {
	GLint loc;
	loc = shader->getUniformLocation(name.c_str());
	glUniformMatrix4fv(loc, size, transpose, data);
}

GLMat3FData::GLMat3FData(string name, GLboolean t, GLsizei num, GLfloat *d, GLenum usg) {
	this->name = name;
	transpose = t;
	size = num;
	data = d;
	usage = usg;
}

void GLMat3FData::setUniform( Shader * shader ) {
	GLint loc;
	loc = shader->getUniformLocation(name.c_str());
	glUniformMatrix3fv(loc, size, transpose, data);
}

GLVec1FData::GLVec1FData(string name, Shader * shader, GLsizei num, float d, GLenum usg) {
	this->name = name;
	loc = glGetUniformLocation(shader->program, name.c_str());
	size = num;
	data = d;
	usage = usg;
	bufID = 0;
}

GLVec2FData::GLVec2FData(string name, Shader * shader, GLsizei num, glm::vec2 d, GLenum usg) {
	this->name = name;
	loc = glGetUniformLocation(shader->program, name.c_str());
	size = num;
	data = glm::vec2( d.x, d.y );
	usage = usg;
	bufID = 0;
}

GLVec3FData::GLVec3FData(string name, Shader * shader, GLsizei num, glm::vec3 d, GLenum usg) {
	this->name = name;
	loc = glGetUniformLocation(shader->program, name.c_str());
	size = num;
	data = glm::vec3( d.x, d.y, d.z );
	usage = usg;
	bufID = 0;
}

GLVec4FData::GLVec4FData(string name, Shader * shader, GLsizei num, glm::vec4 d, GLenum usg) {
	this->name = name;
	loc = glGetUniformLocation(shader->program, name.c_str());
	size = num;
	data = glm::vec4( d.x, d.y, d.z, d.w);
	usage = usg;
	bufID = 0;
}

void GLVec1FData::setUniform( Shader * shader ) {
	glUniform1fv(loc, size, &data);
}

void GLVec2FData::setUniform( Shader * shader ) {
	glUniform2fv(loc, size, glm::value_ptr(data));
}

void GLVec3FData::setUniform( Shader * shader ) {
	glUniform3fv(loc, size, glm::value_ptr(data));
}

void GLVec4FData::setUniform( Shader * shader ) {
	glUniform4fv(loc, size, glm::value_ptr(data));
}

GLVecIData::GLVecIData(string name, GLsizei num, GLsizei vecSize, GLint *d, GLenum usg) {
	this->name = name;
	size = num;
	this->vecSize = vecSize;
	data = d;
	usage = usg;
	bufID = 0;
}


void GLVecIData::setUniform( Shader * shader ) {
	GLint loc;
	loc = shader->getUniformLocation(name.c_str());
	switch (vecSize) {
	case 1:
		glUniform1iv(loc, size, data);
		break;
	case 2:
		glUniform2iv(loc, size, data);
		break;
	case 3:
		glUniform3iv(loc, size, data);
		break;
	case 4:
		glUniform4iv(loc, size, data);
		break;
	default:
		cerr << "**WARNING** GLVecFData::setUniform: "
		<< "unknown size (" << size << ")" << endl;
		break;
	}
}
