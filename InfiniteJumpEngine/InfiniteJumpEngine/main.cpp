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

#include "Shader.h"
#include "Mesh.h"
#include "Level.h"

using namespace std;

int WIN_WIDTH = 1280, WIN_HEIGHT = 720; //window width/height
int main_window;
Level * level;

//glui interface variables
float   transX = 0;
float   transY = 0;
float   transZ = 0;
float   rotX = 0;
float   rotY = 0;

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
	main_window = glutCreateWindow("InfiniteJump Engine");

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
}

//initialize OpenGL background color and vertex/normal arrays
void buildTriangle() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	level->camera->cam = glm::lookAt(glm::vec3(0,6,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(WIN_WIDTH) / glm::float_t(WIN_HEIGHT),
		glm::float_t(0.1),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 10.0f, 0.0 );

	//initiallize vertex and normal arrays
	//this is where you might want to read in your model
	Entity * entity = new Entity( );
	Mesh * mesh = new Mesh( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
	mesh->addVert(-1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,-1, 0,1,0, 0,1,0);

	mesh->addVert(-1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,-1, 0,1,0, 0,1,0);
	mesh->addVert(-1,0,-1, 0,1,0, 0,1,0);

	entity->addComponent(mesh);

	level->addEntity(entity);
}

void initLevel() {
	if ( level ) { 
		delete level;
	}
	level = new Level( );
}

void setupInterface( ) {
    GLUI *glui = GLUI_Master.create_glui( "GLUI" );
    glui->set_main_gfx_window( main_window );

    GLUI_Panel *main_panel = glui->add_panel("Golf Cup Interface");

    GLUI_Spinner *trans1_spinner =
    glui->add_spinner_to_panel( main_panel, "Cup position on x-axis:", GLUI_SPINNER_FLOAT, &transX );
    trans1_spinner->set_float_limits(-50, 50);

    GLUI_Spinner *trans2_spinner =
    glui->add_spinner_to_panel( main_panel, "Cup position on y-axis:", GLUI_SPINNER_FLOAT, &transY );
    trans2_spinner->set_float_limits(-50, 50);

    GLUI_Spinner *trans3_spinner =
    glui->add_spinner_to_panel( main_panel, "Cup position on z-axis:", GLUI_SPINNER_FLOAT, &transZ );
    trans3_spinner->set_float_limits(-50, 50);

    GLUI_Spinner *angleX_spinner =
    glui->add_spinner_to_panel( main_panel, "Angle on x-axis:", GLUI_SPINNER_FLOAT, &rotX);
    angleX_spinner->set_float_limits(-360, 360);

    GLUI_Spinner *angleY_spinner =
    glui->add_spinner_to_panel( main_panel, "Angle on y-axis:", GLUI_SPINNER_FLOAT, &rotY);
    angleY_spinner->set_float_limits(-360, 360);

    /* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc( idle );

}

int main(int argc, char **argv) {
	level = new Level();
	glutInit(&argc, argv);
	setupGLUT();

	setupInterface( );

	glewInit();

	initLevel();

	//temp function
	buildTriangle();

	glutMainLoop();

	delete level;

	return 0;
}



