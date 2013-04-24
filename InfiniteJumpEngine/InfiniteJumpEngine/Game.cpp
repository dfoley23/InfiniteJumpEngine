#include "Game.h"

Game* Game::inst = NULL;


Game::Game(void)
{
	WIN_WIDTH = 1280;
	WIN_HEIGHT = 720;
	resman = NULL;
	level = NULL;
	glui = NULL;
	//glui interface variables
	transX = 0.0f;
	transY = 0.0f;
	transZ = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
}


Game::~Game(void)
{
	for (componentIter c = components.begin(); c != components.end(); c++){
		delete (*c);
	}
}

void Game::setupGLUT(){
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	main_window = glutCreateWindow("InfiniteJump Engine");
}

void Game::reshape(int w, int h){
	WIN_WIDTH = w;
	WIN_HEIGHT = h;
	if (level){
		level->camera->proj = glm::perspective(
			glm::float_t(45),
			glm::float_t(WIN_WIDTH) / glm::float_t(WIN_HEIGHT),
			glm::float_t(0.1),
			glm::float_t(1000.0)
			);
	}
}

void Game::display(){
	glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (level){
		level->update(0.0f);
		level->draw();
	}

	glutSwapBuffers();
}

void Game::idle(){
	glutPostRedisplay();
}

void Game::keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void Game::setupInterface(){
	glui = GLUI_Master.create_glui( "GLUI" );
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
		glui->add_spinner_to_panel( main_panel, "Cup Angle on x-axis:", GLUI_SPINNER_FLOAT, &rotX);
	angleX_spinner->set_float_limits(-360, 360);

	GLUI_Spinner *angleY_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup Angle on y-axis:", GLUI_SPINNER_FLOAT, &rotY);
	angleY_spinner->set_float_limits(-360, 360);

}

int Game::run(int argc, char** argv){
	resman = new ResManager();
	if ( argc > 1 ) {
		string directory = "Levels/";
		level = resman->getTriangleLevel(directory + argv[1]);
	} else {
		level = buildTestLevel( );
	}

	level->camera->cam = glm::lookAt(glm::vec3(0,4,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(getGame()->getWinWidth()) / glm::float_t(getGame()->getWinHeight()),
		glm::float_t(0.1),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 10.0f, 0.0 );

	glutMainLoop();
	return 0;
}


Level * Game::buildTestLevel( ) {
	Level *level = new Level();

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
	return level;
}