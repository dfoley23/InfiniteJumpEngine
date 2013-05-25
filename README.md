InfiniteJumpEngine
==================
Authors:
Kevin Cameron
Dennis Foley


To run the project the debug/release exe has to be in the same folder as these folders/files 
shaders/pointLight.vert
shaders/pointLight.frag
shaders/spriteBasic.vert
shaders/spriteBasic.frag
Levels/
Assets/
freeglut.dll
glew32.dll

to run a level go to the directory of the exe in a command window type InfiniteJumpEngine.exe hole.xx.db 
the level files have to be in a directory called Levels under the directory where the exe is

to run a course you can enter InfiniteJumpEngine.exe course.db
or InfiniteJumpEngine.exe course.db n (to jump to the nth hole of the course)


CAMERA CONTROLS: (only available in free look)
CAMERA UP ON Y AXIS: Arrow Key Up
CAMERA DOWN ON Y AXIS: Arrow Key down
CAMERA RIGHT ON X AXIS: Arrow Key right
CAMERA LEFT ON X AXIS: Arrow Key left
CAMERA ZOOM IN: Scroll wheel on mouse forward
CAMERA ZOOM OUT: Scroll wheel on mouse backward

CAMERA VIEWS
0 IS THIRD PERSON PERSPECTIVE
1 IS FIRST PERSON PERSPECTIVE
2 IS TOP DOWN PERSPECTIVE
3 IS FREE LOOK USE CAMERA CONTROLS ABOVE

GAME CONTROLS
Click and drag the mouse opposite the direction you want to shoot the ball

To shoot NORTH, DRAG THE MOUSE from TOP TO BOTTOM on the screen
To shoot SOUTH, DRAG THE MOUSE from BOTTOM TO TOP on the screen
To shoot EAST, DRAG THE MOUSE FROM RIGHT TO LEFT on the screen
To shoot WEST, DRAG THE MOUSE FROM LEFT TO RIGHT on the screen

THE COMPASS will tell you which way is north 
while in third or first person perspective use the compass for orientation
