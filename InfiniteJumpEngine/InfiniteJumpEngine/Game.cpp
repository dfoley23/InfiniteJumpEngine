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
	camEyeX = 0.0f;
	camEyeY = 4.0f;
	camEyeZ = 6.0f;
	camLookAtX = 0.0f;
	camLookAtY = 0.0f;
	camLookAtZ = 0.0f;
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
	glEnable(GL_DEPTH_TEST);	

	level->camera->cam = glm::lookAt( glm::vec3( camEyeX, camEyeY, camEyeZ ), 
		glm::vec3( camLookAtX, camLookAtY, camLookAtZ ), glm::vec3( 0, 1, 0 ) );

	level->cupMeshToMove->rotate( rotX, rotY, 0);
	level->cupMeshToMove->translate( transX, transY, transZ );
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
	glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_LEFT );
	glui->set_main_gfx_window( main_window );

	GLUI_Panel *main_panel = glui->add_panel("Golf Cup Interface");
	GLUI_Panel *cam_panel = glui->add_panel( "Camera Interface");

	GLUI_Spinner *trans1_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup position on x-axis:", GLUI_SPINNER_FLOAT, &transX );
	trans1_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans2_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup position on y-axis:", GLUI_SPINNER_FLOAT, &transY );
	trans2_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans3_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup position on z-axis:", GLUI_SPINNER_FLOAT, &transZ );
	trans3_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *angleX_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup Angle on x-axis:", GLUI_SPINNER_FLOAT, &rotX);
	angleX_spinner->set_float_limits(-360, 360);

	GLUI_Spinner *angleY_spinner =
		glui->add_spinner_to_panel( main_panel, "Cup Angle on y-axis:", GLUI_SPINNER_FLOAT, &rotY);
	angleY_spinner->set_float_limits(-360, 360);

	//camera controls
	GLUI_Spinner *transCam1_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam X pos:", GLUI_SPINNER_FLOAT, &camEyeX );
	transCam1_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *transCam2_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam Y pos:", GLUI_SPINNER_FLOAT, &camEyeY );
	transCam2_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *transCam3_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam Z pos:", GLUI_SPINNER_FLOAT, &camEyeZ );
	transCam3_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamX_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam X angle:", GLUI_SPINNER_FLOAT, &camLookAtX);
	angleCamX_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamY_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam Y angle:", GLUI_SPINNER_FLOAT, &camLookAtY);
	angleCamY_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamZ_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam Z angle:", GLUI_SPINNER_FLOAT, &camLookAtZ);
	angleCamZ_spinner->set_float_limits(-10, 10);
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
		glm::float_t(0.1f),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 100.0f, -3.0 );

	glutMainLoop();
	return 0;
}


Level * Game::buildTestLevel( ) {
	Level *level = new Level();

	//initiallize vertex and normal arrays
	//this is where you might want to read in your model
	vector<glm::vec3> groundVerts;
	groundVerts.push_back(glm::vec3(-1,0,1));
	groundVerts.push_back(glm::vec3(1,0,1));
	groundVerts.push_back(glm::vec3(1,0,-1));
	groundVerts.push_back(glm::vec3(-1,0,-1));

	vector<int> noNeighbors;
	Entity * entity = new Entity();
	Tile * groundTile = new Tile( 0 , groundVerts, noNeighbors, glm::vec3(0, 0.75f, 0));
	TileSet * tileSet = new TileSet();
	tileSet->addTile(groundTile);
	//entity->addComponent(tileSet);
	entity->addComponent(groundTile);
	level->addEntity(entity);

	Entity * cupEntity = new Entity( );
	Mesh * cup = new Mesh( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
	float x = 0.5f;
	float y = 0.0f;
	float z = 0.5f;
	//cup mesh

	glm::vec3 vert0 = glm::vec3( x, y, z );
	glm::vec3 vert1 = glm::vec3( x, y, z+0.25f );
	glm::vec3 color = glm::vec3( 0, 0, 0 );
	cup->createYCube( 0.25f, 0.002f, vert0, vert1, color );

	cupEntity->addComponent( cup );
	level->addEntity( cupEntity );
	level->cupMeshToMove = cup;

	return level;
}