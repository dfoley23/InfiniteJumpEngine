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
	picking = 0;
	cameraProfile = 4;
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

	//update camera 
	switch( cameraProfile ) {
	case 0:
		level->camera->cam = glm::lookAt( glm::vec3( level->pickedMesh->getCenter().x, 
			level->pickedMesh->getCenter().y + 0.25f,
			level->pickedMesh->getCenter().z + 0.25f ),
			level->pickedMesh->getCenter(), glm::vec3( 0, 1, 0 ) );
		break;
	case 1:
		level->camera->cam = glm::lookAt( glm::vec3( level->pickedMesh->getCenter().x, 
			level->pickedMesh->getCenter().y,
			level->pickedMesh->getCenter().z-0.05f ),
			glm::vec3( level->pickedMesh->getCenter().x, 
			level->pickedMesh->getCenter().y,
			level->pickedMesh->getCenter().z-1.0f ), glm::vec3( 0, 1, 0 ) );
		break;
	case 2:
		level->camera->cam = glm::lookAt( glm::vec3( level->pickedMesh->getCenter().x, 
			level->pickedMesh->getCenter().y+6.0f,
			level->pickedMesh->getCenter().z ),
			level->pickedMesh->getCenter(), glm::vec3( 0, 0, 1 ) );
		break;
	default:
		break;
	}

	if (level){
		level->update(0.0f);
		level->draw();
	}

	glutSwapBuffers();
}

void Game::displayForPick( int x, int y ) {
	if ( picking ) {
		glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);	

		level->drawForPick( );

		pixel_t * pixels = (pixel_t *) malloc(getWinWidth()*getWinHeight() * sizeof(pixel_t));

		glReadPixels(0,0,getWinWidth(),getWinHeight(),GL_RGBA,GL_UNSIGNED_BYTE,(void *)pixels);

		pixel_t p = PIXEL(pixels, x, getWinHeight()-y, getWinWidth() );
		float r = (float)RED(p);
		float g = (float)GREEN(p);
		float b = (float)BLUE(p);
		if ( r != 0 || g != 0 || b != 0 ) {
			for(int i = 0; i < static_cast<int>(level->getEntities().size()); i++) {
				for (int j=0; j< static_cast<int>(level->getEntities().at(i)->getComponents().size()); j++){
					if ( level->getEntities().at(i)->getComponents().at(j)->getPickId().x == r && 
						level->getEntities().at(i)->getComponents().at(j)->getPickId().y == g && 
						level->getEntities().at(i)->getComponents().at(j)->getPickId().z == b ) {
							level->pickedMesh = (Mesh*)(level->getEntities().at(i)->getComponents().at(j));
					}
				}
			}
		}
		free(pixels);
	}
}

void Game::idle(){
	glutPostRedisplay();
}

void Game::keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
		break;
	case 97: //a
		level->ball->applyImpulse( glm::vec3( 0.1, 0, 0.1 ) );
		break;
	default:
		break;
	}
}

void Game::glui_callBack( int id ) {
	switch(id) {
	case 0:
		level->camera->cam = glm::lookAt( glm::vec3( camEyeX, camEyeY, camEyeZ ), 
			glm::vec3( camLookAtX, camLookAtY, camLookAtZ ), glm::vec3( 0, 1, 0 ) );
		cameraProfile = 4;
		break;
	case 1:
		break;
	case 2:
		level->pickedMesh->translate( transX, transY, transZ );
		break;
	case 3:
		level->pickedMesh->rotate( rotX, rotY, 0);
		break;
	default:
		break;
	}
}


void Game::setupInterface( void(*cb)(int i) ){
	glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_LEFT );
	glui->set_main_gfx_window( main_window );

	GLUI_Panel *cam_panel = glui->add_panel( "Camera Interface");
	GLUI_Panel *mesh_panel = glui->add_panel("Move Selected Mesh ");
	GLUI_RadioGroup *camProfiles= glui->add_radiogroup_to_panel( cam_panel, &cameraProfile, 1, cb );

	//camera controls
	//profiles
	GLUI_RadioButton *thirdPersonCamera = glui->add_radiobutton_to_group( camProfiles, "Third Person View" );
	GLUI_RadioButton *firstPersonCamera = glui->add_radiobutton_to_group( camProfiles, "First Person View" );
	GLUI_RadioButton *topDownCamera = glui->add_radiobutton_to_group( camProfiles, "Top Down View" );

	GLUI_Spinner *transCam1_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam eye X:", GLUI_SPINNER_FLOAT, &camEyeX, 0, cb );
	transCam1_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *transCam2_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam eye Y:", GLUI_SPINNER_FLOAT, &camEyeY, 0, cb );
	transCam2_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *transCam3_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam eye Z:", GLUI_SPINNER_FLOAT, &camEyeZ, 0, cb );
	transCam3_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamX_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam look at X:", GLUI_SPINNER_FLOAT, &camLookAtX, 0, cb);
	angleCamX_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamY_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam look at Y:", GLUI_SPINNER_FLOAT, &camLookAtY, 0, cb);
	angleCamY_spinner->set_float_limits(-10, 10);

	GLUI_Spinner *angleCamZ_spinner =
		glui->add_spinner_to_panel( cam_panel, "Cam look at Z:", GLUI_SPINNER_FLOAT, &camLookAtZ, 0, cb);
	angleCamZ_spinner->set_float_limits(-10, 10);

	//picking mesh interface
	GLUI_Checkbox *picking_check = glui->add_checkbox_to_panel(  mesh_panel, "pick mode", &picking );

	GLUI_Spinner *trans1_spinner =
		glui->add_spinner_to_panel( mesh_panel, "mesh x pos:", GLUI_SPINNER_FLOAT, &transX, 2, cb );
	trans1_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans2_spinner =
		glui->add_spinner_to_panel( mesh_panel, "mesh y pos:", GLUI_SPINNER_FLOAT, &transY, 2, cb );
	trans2_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans3_spinner =
		glui->add_spinner_to_panel( mesh_panel, "mesh z pos:", GLUI_SPINNER_FLOAT, &transZ, 2, cb );
	trans3_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *angleX_spinner =
		glui->add_spinner_to_panel( mesh_panel, "mesh angle on x", GLUI_SPINNER_FLOAT, &rotX, 3, cb);
	angleX_spinner->set_float_limits(-360, 360);

	GLUI_Spinner *angleY_spinner =
		glui->add_spinner_to_panel( mesh_panel, "mesh angle on y:", GLUI_SPINNER_FLOAT, &rotY, 3, cb);
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
		glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
		glm::float_t(0.1f),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 100.0f, 0.0 );


	transX = level->pickedMesh->getCenter().x;
	transY = level->pickedMesh->getCenter().y;
	transZ = level->pickedMesh->getCenter().z;

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
	tileSet->addTile( 0, groundTile);
	//entity->addComponent(tileSet);
	entity->addComponent(groundTile);
	level->addEntity(entity);

	Entity * cupEntity = new Entity( );
	Mesh * cup = new Mesh( );
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
	level->pickedMesh = cup;

	return level;
}