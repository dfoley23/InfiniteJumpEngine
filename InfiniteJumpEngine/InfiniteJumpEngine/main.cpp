#include "glIncludes.h"
#include "Game.h"

//reshape function for GLUT
void reshape(int w, int h) {
	Game::game()->reshape(w,h);
}

//display function for GLUT
void display() {
	Game::game()->display();
}

//idle function for GLUT
void idle() {
	Game::game()->idle();
}

//captures keyborad input for GLUT
void keyboard(unsigned char key, int x, int y) {
	Game::game()->keyboard(key,x,y);
}


void mouse_click(int button, int state, int x, int y) {
	Game::game( )->mouse_click(button, state, x, y);
}

void mouse_drag( int x, int y ) {
	Game::game( )->mouse_drag(x, y);
}

//do some GLUT initialization
void setupGLUT() {
	Game::game()->setupGLUT();

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutMouseFunc(mouse_click);

	glutIdleFunc(display);
}

void setupInterface( void(*cb)(int i) ) {
	Game::game()->setupInterface( cb );
}

void glui_callBack( int i ) {
	Game::game()->glui_callBack(i);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);

	setupGLUT();
	
	setupInterface( &glui_callBack );

	/* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc( idle );

	glewInit();

	Game::game()->run(argc, argv);

	Game::clear();

	return 0;
}
