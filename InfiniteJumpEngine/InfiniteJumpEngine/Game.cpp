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
	hasPressed = false;
	holeStrokeCount = 0;
	totalStrokeCount = 0;
	totalPar = 0;
	curPar = 0;
	lua = new LuaBaseComponent();
}


Game::~Game(void)
{
	for (componentIter c = components.begin(); c != components.end(); c++){
		delete (*c);
	}
	delete lua;
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
	glClearColor( 1, 1, 1, 1 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	t_delta = IJTime() - t_init;
	if (level){
		level->update((float)t_delta.getSeconds());
		t_init.reset();

		if (sub_levelID >= 0 ) {
			glm::vec3 pos = level->ball->getPhysics()->getKinematics()->loc.getPosition();
			glm::vec3 dir = level->ball->getPhysics()->getKinematics()->vel.getPosition();

			level->camera->update( pos, dir );
		}
		level->draw();

	}
	glutSwapBuffers();
	if ( level->ball  != NULL ) {
	if ( level->ball->hitCup ) {
		switchLevel( );
	}
	}
}

void Game::displayForPick( int x, int y ) {

}

void Game::idle(){
	glutSetWindow(main_window);
	glutPostRedisplay();
	//Sleep (100);
}

void Game::glui_callBack( int id ){

}

void Game::setupInterface( void(*cb)(int i) ){
	glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_TOP );
	glui->set_main_gfx_window( main_window );

	GLUI_Panel *mainPanel = glui->add_panel( "" );

	holePar = glui->add_statictext_to_panel( mainPanel, "Par Num" );
	holeScore = glui->add_statictext_to_panel( mainPanel, "Score: 0" );
	glui->add_column_to_panel( mainPanel, true );
	string spacer = " ";
	for( int i=0; i<10; i++) {
		spacer = spacer + " ";
	}
	glui->add_statictext_to_panel( mainPanel, spacer.c_str() );
	glui->add_column_to_panel( mainPanel, false );
	//courseName = glui->add_statictext_to_panel( mainPanel, "Course Name" );
	holeName = glui->add_statictext_to_panel( mainPanel, "Hole Number: Name" );
	spacer = " ";
	for( int i=0; i<225; i++) {
		spacer = spacer + " ";
	}
	glui->add_statictext_to_panel( mainPanel, spacer.c_str() );
	glui->add_column_to_panel( mainPanel, true );
	totalScore = glui->add_statictext_to_panel( mainPanel, "Total Score: Num" );

	//fps_text = std::string("Hello World!");
	//fps_gauge = glui->add_edittext_to_panel( mesh_panel, "FPS:", fps_text);
}

void Game::mouse_click(int button, int state, int x, int y){ 
	//luabind::call_function<int>(lua->getState(), "mouseclick_cb", button, state, x, y);
		if ( level->ballDirHud  != NULL ) {
			if(state==GLUT_DOWN && !hasPressed ){
				clickPoint = glm::vec3( x, 0, y );
				float scaledX = ((2.f*(float)x ) / ( (float)getWinWidth() )) - 1.f;
				float scaledY = ((-2.f*(float)y ) / ( (float)getWinHeight() )) + 1.f;
				level->ballDirHud->translate( scaledX, scaledY, 0 );
				hasPressed = true;
			} else if ( state==GLUT_UP && hasPressed ) {
				holeStrokeCount++;
				curScore = holeStrokeCount - curPar;
				string curScore_str;
				stringstream out;
				out << curScore;
				curScore_str = out.str();
				if ( curScore > 0 )
					curScore_str = "+" + curScore_str;
				string complete = "Hole Score: " + curScore_str;
				this->holeScore->set_text( complete.c_str() );
				glm::vec3 releasePoint = glm::vec3( x, 0, y);
				glm::vec3 dir = -( releasePoint - clickPoint );
				if ( glm::length( dir ) > 100 ) {
					dir = glm::normalize( dir ) * 3.f;
				} else if ( glm::length( dir ) > 50 ) {
					dir = glm::normalize( dir ) * 2.f;
				} else {
					dir = glm::normalize( dir );
				}
				//cout << dir.x << " : " << dir.z << endl;
				if ( glm::length( dir ) > 0.07f ) {
					sendMessage(level->ball, NULL, "shoot", glm::vec4(dir, 0.f));
				}
				level->ballDirHud->scale( 1, 1, 1 );
				level->ballDirHud->rotate( 0, glm::vec3( 0, 0, 1 ) );
				hasPressed = false;
			}
		}
}

/*
* mouse-drag function
*/
void Game::mouse_drag(int x, int y){
	//luabind::call_function<int>(lua->getState(), "mousedrag_cb", x, y);
	if ( level->ballDirHud != NULL ) {
		glm::vec3 curPos = level->ballDirHud->getCenter();
		float scaledX = ((16.f*(float)x ) / ( (float)getWinWidth() )) - 8.f;
		float scaledY = ((16.f*(float)y ) / ( (float)getWinHeight() )) - 8.f;
		if ( glm::abs(curPos.y-scaledY) > 0 ) {
			glm::vec3 dragPoint = glm::vec3( x, 0, y );
			level->ballDirHud->scale( 1, 1+(glm::abs(curPos.y-scaledY)), 1 );
			glm::vec3 dir = -( dragPoint - clickPoint );
			float angle = glm::acos( glm::dot( glm::normalize(dir), glm::vec3( 0, 0, -1 ) ) );
			if ( x > clickPoint.x ) {
				angle = -angle;
			}
			level->ballDirHud->rotate( angle*rad_to_deg, glm::vec3( 0, 0, -1 ) );
		} else if ( glm::abs( curPos.x-scaledX) > 0 ) {
			glm::vec3 dragPoint = glm::vec3( x, 0, y );
			level->ballDirHud->scale( 1, 1+(glm::abs(curPos.x-scaledX)), 1 );
			glm::vec3 dir = -( dragPoint - clickPoint );
			float angle = glm::acos( glm::dot( glm::normalize(dir), glm::vec3( 0, 0, -1 ) ) );
			if ( x > clickPoint.x ) {
				angle = -angle;
			}
			level->ballDirHud->rotate( angle*rad_to_deg, glm::vec3( 0.f, 0.f, -1.f ) );
		}
	}
}

/*
* mouse middle wheel function
*/
void Game::mouse_wheel( int wheel, int direction, int x, int y) {
	luabind::call_function<int>(lua->getState(), "mousewheel_cb", wheel, direction, x, y);
}

/*
* the arrow key function
* value of left is 100
* value of right is 102
* value of up is 101
* value of down is 103
*/
void Game::special_keyboard(int key, int x, int y) {  
	luabind::call_function<int>(lua->getState(), "spec_keyboard_cb", key);
}

/*
* the main keyboard function
*/
void Game::keyboard(unsigned char key,int x, int y){
	//call the lua function
	luabind::call_function<int>(lua->getState(), "keyboard_cb", key);
	switch (key) {
	case 32: //space
		if (sub_levelID < 0 ) {
			sub_levelID = 0;
			level->clear();
			delete level;
			resman->clearTextures();
			level = resman->getTriangleLevel(levelID, sub_levelID);
			level->camera->cam = glm::lookAt(glm::vec3(0,4,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
			level->camera->proj = glm::perspective(
				glm::float_t(45),
				glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
				glm::float_t(0.1f),
				glm::float_t(1000.0)
				);
			level->camera->lightPos = glm::vec3( 0.0, 100.0f, 0.0 );
		}
		break;
	case 27: // escape
		exit(0);
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
	case 119: //w
		if ( sub_levelID >= 0 ) 
			sendMessage(level->ball, NULL, "forward");
		break;
	case 97: //a
		if ( sub_levelID >= 0 ) 
			sendMessage(level->ball, NULL, "left");
		break;
	case 115: //s
		if ( sub_levelID >= 0 ) 
			sendMessage(level->ball, NULL, "back");
		break;
	case 100: //d
		if ( sub_levelID >= 0 ) 
			sendMessage(level->ball, NULL, "right");
		break;
	default:
		break;
	}
}

/*
* switches the level
*/
void Game::switchLevel( ) {
	string totScore_str;
	stringstream out;
	totalStrokeCount+=curScore;
	out << totalStrokeCount;
	totScore_str = out.str();
	if ( totalStrokeCount > 0 )
		totScore_str = "+" + totScore_str;
	string complete = "Total Score: " + totScore_str;
	this->totalScore->set_text( complete.c_str() );

	scores.registerScore(sub_levelID,holeStrokeCount);
	cout << "Hole:" << sub_levelID
		 << " Score:" << scores.getCurrentScore(sub_levelID) 
		 << " Best:" << scores.getHighScore(sub_levelID)
		 <<endl;
	sub_levelID++;
	if ( sub_levelID > level->maxSubLevels ) {
		sub_levelID = 0;
	}
	level->clear();
	delete level;
	level = resman->getTriangleLevel(levelID, sub_levelID);
	luabind::call_function<void>(lua->getState(), "registerObject", "camera", boost::shared_ptr<Camera>( level->camera ) );
	luabind::call_function<void>(lua->getState(), "setInitialCameraPos", 0 );	
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
		glm::float_t(0.1f),
		glm::float_t(1000.0)
		);
}

LuaBaseComponent * Game::getLuaBase( ){
	return lua;
}

/*
* the main run method that handles a game
*/
int Game::run(int argc, char** argv){
	resman = new ResManager();
	//make a new lua state for input functions
	luaL_dofile( lua->getState(), "main.lua" );

	for (int a = 0; a < argc; a++){
		try {
			luabind::call_function<int>(lua->getState(), "registerArg", argv[a]);
		} catch (luabind::error &e){
			cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
		}
	}
	try {
		luabind::call_function<int>(lua->getState(), "loadDefaultScene");
	} catch (luabind::error &e){
		cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
	}
	try {
		exposeClassesToLua( );
	} catch (luabind::error &e){
		cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
	}


	char* profileName = "default";
	if ( argc > 1 ) {
		string directory = "Levels/";
		levelID = directory + argv[1];
		sub_levelID = -1;
		if ( argc > 2 ) {
			sub_levelID = atoi( argv[2] );
		}
		level = resman->getTriangleLevel(directory + argv[1], sub_levelID);
	} else {
		string directory = "Levels/course.db";
		levelID = directory;
		sub_levelID = -1;
		level = resman->getTriangleLevel(directory, sub_levelID);
	}
	
	scores.loadProfile(profileName);
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(getWinWidth()) / glm::float_t(getWinHeight()),
		glm::float_t(0.1f),
		glm::float_t(1000.0)
		);
	try {
	luabind::call_function<void>(lua->getState(), "registerObject", "camera", boost::shared_ptr<Camera>( level->camera ) );
	}catch (luabind::error &e){
		cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
	}
	try {
	luabind::call_function<void>(lua->getState(), "setInitialCameraPos" );
	}catch (luabind::error &e){
		cerr << "Lua Error:" << lua_tostring( e.state(), -1) << "\n";
	}

	glutMainLoop();
	return 0;
}

float glmdot ( float ux, float uy, float uz, float vx, float vy, float vz ) {
	glm::vec3 u = glm::vec3( ux, uy, uz );
	glm::vec3 v = glm::vec3( vx, vy, vz );
	return glm::dot( u, v );
}

glm::vec3 glmcross ( float ux, float uy, float uz, float vx, float vy, float vz ) {
	glm::vec3 u = glm::vec3( ux, uy, uz );
	glm::vec3 v = glm::vec3( vx, vy, vz );
	return glm::cross( u, v );
}

glm::vec3 glmnormalize( float ux, float uy, float uz ) {
	glm::vec3 u = glm::vec3( ux, uy, uz );
	return glm::normalize( u );
}

float glmlength ( float ux, float uy, float uz ) {
	glm::vec3 u = glm::vec3( ux, uy, uz );
	return glm::length( u );
}

float glmacos( float dx ) {
	return glm::acos( dx );
}

/*
* exports useful functions and classes to the lua state
*
*/
void Game::exposeClassesToLua( ) {
	luabind::module(lua->getState( )) [
		//FUNCTIONS
		luabind::def("dot", glmdot ),
			luabind::def("cross", glmcross),
			luabind::def("acos", glmacos),
			luabind::def("length", glmlength),
			luabind::def("normalize", glmnormalize),

			//CLASSES
			luabind::class_<glm::vec3>("vec3")
			.def(luabind::constructor<>())
			.def_readwrite( "x", &glm::vec3::x )
			.def_readwrite( "y", &glm::vec3::y )
			.def_readwrite( "z", &glm::vec3::z )
			.def(constructor<float, float, float>())
			.def(constructor<glm::vec3&>()),

			luabind::class_<glm::vec4>("vec4")
			.def(luabind::constructor<>())
			.def_readwrite( "x", &glm::vec4::x )
			.def_readwrite( "y", &glm::vec4::y )
			.def_readwrite( "z", &glm::vec4::z )
			.def_readwrite( "w", &glm::vec4::w )
			.def(constructor<float, float, float, float>())
			.def(constructor<glm::vec4&>()),

			luabind::class_<Camera>("Camera")
			.def(luabind::constructor<>())
			.def("switchProfile", &Camera::switchProfile)
			.def("changeEyePos", &Camera::changeEyePos)
			.def("changeLookAtPos", &Camera::changeLookAtPos)
			.def("changeLightPos", &Camera::changeLightPos),

			luabind::class_<Component>("Component")
			.def(luabind::constructor<>())
			.def("sendMessage", (void( Component::*)(Component*, Component*, const char*, float, float, float, float ))&Component::sendMessage )
			.def("receiveMessage", &Component::receiveMessage )
			.def("getParent", &Component::getParent ),

			luabind::class_<Mesh>("Mesh")
			.def(luabind::constructor<>())
			.def(luabind::constructor<Mesh*>())
			.def("translate", &Mesh::translate)
			.def("rotate", (void( Mesh::*)(float, glm::vec3))&Mesh::rotate)
			.def("rotate", (void( Mesh::*)(float, float, float))&Mesh::rotate)
			.def("scale", &Mesh::scale)
			.def("addVert", (void( Mesh::*)(glm::vec3, glm::vec3, glm::vec3, glm::vec2))&Mesh::addVert)
			.def("createYCube", (void( Mesh::*)( 
			float, float, glm::vec3, glm::vec3, glm::vec3 ))&Mesh::createYCube )
			.def("changeColor", &Mesh::changeColor )
			.def("getCenter", &Mesh::getCenter )
	];
	//luabind::object table = luabind::newtable( lua->getState( ) );
	//luabind::globals(lua->getState( ))[ "registryTable" ] = table;
}
