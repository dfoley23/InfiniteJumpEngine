#include "Game.h"

Game* Game::inst = NULL;


Game::Game(void)
{
	parent = NULL;
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
	hasPressed = false;
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

	t_delta = IJTime() - t_init;
	if (level){
		//if ( t_delta.getSeconds() > MIN_DT ) 
		{
			fps_gauge->set_float_val(1.0/t_delta.getSeconds());
			level->update(t_delta.getSeconds());
			t_init.reset();
		}

		glm::vec3 pos = level->ball->getPhysics()->getKinematics()->loc.getPosition();
		glm::vec3 dir = level->ball->getPhysics()->getKinematics()->vel.getPosition();

		level->camera->update( pos, dir );
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
	glutSetWindow(main_window);
	glutPostRedisplay();
	Sleep (100);
}

void Game::glui_callBack( int id ) {
	glm::vec3 pos = level->ball->getPhysics()->getKinematics()->loc.getPosition();
	switch(id) {
	case 0:
		level->camera->cam = glm::lookAt( glm::vec3( camEyeX, camEyeY, camEyeZ ), 
			glm::vec3( camLookAtX, camLookAtY, camLookAtZ ), glm::vec3( 0, 1, 0 ) );
		level->camera->switchProfile( 4 );
		break;
	case 1:
		level->camera->switchProfile( cameraProfile );
		break;
	case 2:
		level->ball->getPhysics()->getKinematics()->acc.setPosition( glm::vec3( 0, 0, 0) );
		level->ball->getPhysics()->getKinematics()->vel.setPosition( glm::vec3( 0, 0, 0) );
		sendMessage(level->ball->getPhysics()->getKinematics(), NULL, "translate", glm::vec4(pos.x+transX, pos.y, pos.z,0.f));
		break;
	case 3:
		sendMessage(level->ball->getPhysics()->getKinematics(), NULL, "translate", glm::vec4(pos.x, pos.y+transY, pos.z,0.f));
		break;
	case 4:
		sendMessage(level->ball->getPhysics()->getKinematics(), NULL, "translate", glm::vec4(pos.x, pos.y, pos.z+transZ,0.f));
		break;
	case 5:
		//sendMessage(level->ball->getPhysics()->getKinematics(), NULL, "rotate", glm::vec4(rotX, rotY, 0.f,0.f));
		break;
	default:
		break;
	}
}


void Game::setupInterface( void(*cb)(int i) ){
	glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_LEFT );
	glui->set_main_gfx_window( main_window );

	GLUI_Panel *cam_panel = glui->add_panel( "Camera Interface");
	GLUI_Panel *mesh_panel = glui->add_panel(" ");
	GLUI_RadioGroup *camProfiles= glui->add_radiogroup_to_panel( cam_panel, &cameraProfile, 1, cb );

	//camera controls
	//profiles
	GLUI_RadioButton *thirdPersonCamera = glui->add_radiobutton_to_group( camProfiles, "Third Person View" );
	GLUI_RadioButton *firstPersonCamera = glui->add_radiobutton_to_group( camProfiles, "First Person View" );
	GLUI_RadioButton *topDownCamera = glui->add_radiobutton_to_group( camProfiles, "Top Down View" );
	GLUI_RadioButton *freeLook = glui->add_radiobutton_to_group( camProfiles, "Free Look View" );

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
	/*GLUI_Checkbox *picking_check = glui->add_checkbox_to_panel(  mesh_panel, "pick mode", &picking );

	GLUI_Spinner *trans1_spinner =
	glui->add_spinner_to_panel( mesh_panel, "mesh x pos:", GLUI_SPINNER_FLOAT, &transX, 2, cb );
	trans1_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans2_spinner =
	glui->add_spinner_to_panel( mesh_panel, "mesh y pos:", GLUI_SPINNER_FLOAT, &transY, 3, cb );
	trans2_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *trans3_spinner =
	glui->add_spinner_to_panel( mesh_panel, "mesh z pos:", GLUI_SPINNER_FLOAT, &transZ, 4, cb );
	trans3_spinner->set_float_limits(-5, 5);

	GLUI_Spinner *angleX_spinner =
	glui->add_spinner_to_panel( mesh_panel, "mesh angle on x", GLUI_SPINNER_FLOAT, &rotX, 5, cb);
	angleX_spinner->set_float_limits(-360, 360);

	GLUI_Spinner *angleY_spinner =
	glui->add_spinner_to_panel( mesh_panel, "mesh angle on y:", GLUI_SPINNER_FLOAT, &rotY, 5, cb);
	angleY_spinner->set_float_limits(-360, 360);*/

	fps_text = std::string("Hello World!");
	fps_gauge = glui->add_edittext_to_panel( mesh_panel, "FPS:", fps_text);
}

void Game::mouse_click(int button, int state, int x, int y){ 
	if ( picking ) {
		displayForPick( x, y );
	} else {
		if(state==GLUT_DOWN && !hasPressed ){
			clickPoint = glm::vec3( x, 0, y );
			hasPressed = true;
		} else if ( state==GLUT_UP && hasPressed ) {
			glm::vec3 releasePoint = glm::vec3( x, 0, y);
			glm::vec3 dir = -( releasePoint - clickPoint );
			if ( glm::length( dir ) > 70 ) {
				dir = glm::normalize( dir ) * 2.f;
			} else {
				dir = glm::normalize( dir );
			}
			//cout << dir.x << " : " << dir.z << endl;
			sendMessage(level->ball, NULL, "shoot", glm::vec4(dir, 0.f));
			hasPressed = false;
		}
	}
}

void Game::mouse_drag(int, int ){

}

void Game::keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
		break;
	case 119: //w
		sendMessage(level->ball, NULL, "forward");
		break;
	case 97: //a
		//level->ball->applyImpulse( glm::vec3( 0.03, 0, 0 ) );
		//level->ball->getPhysics()->getKinematics()->vel.setPosition( glm::vec3( 1, 0, 0 ) );
		sendMessage(level->ball, NULL, "left");
		break;
	case 115: //s
		sendMessage(level->ball, NULL, "back");
		break;
	case 100: //d
		sendMessage(level->ball, NULL, "right");
		break;
	case 43: // +
		sub_levelID++;
		level->clear();
		delete level;
		level = resman->getTriangleLevel(levelID, sub_levelID);
		level->camera->cam = glm::lookAt(glm::vec3(0,4,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
		level->camera->proj = glm::perspective(
			glm::float_t(45),
			glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
			glm::float_t(0.1f),
			glm::float_t(1000.0)
			);
		level->camera->lightPos = glm::vec3( 0.0, 100.0f, 0.0 );
	default:
		break;
	}
}

int Game::run(int argc, char** argv){
	resman = new ResManager();
	if ( argc > 1 ) {
		string directory = "Levels/";
		levelID = directory + argv[1];
		sub_levelID = 0;
		if ( argc > 2 ) {
			sub_levelID = atoi( argv[2] );
		}
		level = resman->getTriangleLevel(directory + argv[1], sub_levelID);
	} else {
		string directory = "Levels/hole.01.db";
		levelID = directory;
		sub_levelID = 0;
		level = resman->getTriangleLevel(directory, 0);
	}

	level->camera->cam = glm::lookAt(glm::vec3(0,4,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
		glm::float_t(0.1f),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 100.0f, 0.0 );

	glutMainLoop();
	return 0;
}