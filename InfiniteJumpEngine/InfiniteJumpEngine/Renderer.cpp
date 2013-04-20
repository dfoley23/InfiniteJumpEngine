#define GLEW_STATIC
#include <GL/glew.h> //must include this before gl.h
#include <GL/freeglut.h>

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

#include "Shader.h"
#include "Mesh.h"
#include "Level.h"
using namespace std;

int WIN_WIDTH = 1280, WIN_HEIGHT = 720; //window width/height
Level * level;

//reshape function for GLUT
void reshape(int w, int h) {
	WIN_WIDTH = w;
	WIN_HEIGHT = h;
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(WIN_WIDTH) / glm::float_t(WIN_HEIGHT),
		glm::float_t(0.1),
		glm::float_t(1000.0)
		);
}

//display function for GLUT
void display() {
	glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	level->draw( );

	glutSwapBuffers();
}

//idle function for GLUT
void idle() {
	glutPostRedisplay();
}

//captures keyborad input for GLUT
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

//do some GLUT initialization
void setupGLUT() {
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("InfiniteJump Engine");

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
}

//initialize OpenGL background color and vertex/normal arrays
void buildTriangle() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	level->camera->cam = glm::lookAt(glm::vec3(0,0,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(WIN_WIDTH) / glm::float_t(WIN_HEIGHT),
		glm::float_t(0.1),
		glm::float_t(1000.0)
		);
	//initiallize vertex and normal arrays
	//this is where you might want to read in your model
	Entity * entity = new Entity( );
	Mesh * mesh = new Mesh( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
	mesh->verts.push_back(-1);
	mesh->verts.push_back(-1);
	mesh->verts.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(1);

	mesh->verts.push_back(1);
	mesh->verts.push_back(-1);
	mesh->verts.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(1);

	mesh->verts.push_back(0);
	mesh->verts.push_back(1);
	mesh->verts.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(0);
	mesh->norms.push_back(1);
	
	entity->addComponent(mesh);

	level->entities.push_back(entity);
}

void initLevel() {
	if ( level ) { 
		level->remove( );
		delete level;
	}
	level = new Level( 0 );
}

int main(int argc, char **argv) {
	if ( argc > 1 ) {

	} else {

	}
	glutInit(&argc, argv);
	setupGLUT();

	glewInit();

	initLevel();

	//temp function
	buildTriangle();

	glutMainLoop();

	if (level) 
		level->remove( );
		delete level;

	return 0;
}



