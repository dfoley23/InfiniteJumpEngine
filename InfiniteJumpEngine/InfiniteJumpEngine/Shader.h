
#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h> //must include this before gl.h
#include <GL/freeglut.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
/**
* class Shader
* 
*/

class Shader
{
public:

	// Constructors/Destructors
	//  

	/**
	* Empty Constructor
	*/
	Shader ( );
	Shader(string vertFile, string fragFile) { readFiles(vertFile, fragFile); }
	/**
	* Empty Destructor
	*/
	virtual ~Shader ( );

	/**
	* @param  vertFile
	* @param  fragFile
	*/
	void readFiles (string vertFile, string fragFile )
	{
		//These are shader objects containing the shader source code
		GLint vSource = setShaderSource(vertFile, GL_VERTEX_SHADER);
		GLint fSource = setShaderSource(fragFile, GL_FRAGMENT_SHADER);

		//Create a new shader program
		program = glCreateProgram();

		//Compile the source code for each shader and attach it to the program.
		glCompileShader(vSource);
		printLog("vertex compile log: ", vSource);
		glAttachShader(program, vSource);

		glCompileShader(fSource);
		printLog("fragment compile log: ", fSource);
		glAttachShader(program, fSource);

		//link all of the attached shader objects
		glLinkProgram(program);
	}

	/**
	* @param source file
	* @param type of shader
	*/
	GLint setShaderSource(string fn, GLenum type) {

		FILE *fp;
		char *content = NULL;

		int count=0;

		if (!fn.empty( )) {
			fp = fopen(fn.data( ),"rt");

			if (fp != NULL) {

				fseek(fp, 0, SEEK_END);
				count = ftell(fp);
				rewind(fp);

				if (count > 0) {
					content = (char *)malloc(sizeof(char) * (count+1));
					count = fread(content,sizeof(char),count,fp);
					content[count] = '\0';
				}
				fclose(fp);
			}
		}
		//create the shader
		GLint s = glCreateShader(type);
		glShaderSource(s, 1, const_cast<const char **>(&content), NULL);
		delete [] content;
		return s;
	}


	/**
	* @param  vertFile
	* @param  fragFile
	* @param  geomFile
	*/
	void readFiles (string vertFile, string fragFile, string geomFile )
	{

		//These are shader objects containing the shader source code
		GLint vSource = setShaderSource(vertFile, GL_VERTEX_SHADER);
		GLint gSource = setShaderSource(geomFile, GL_GEOMETRY_SHADER);
		GLint fSource = setShaderSource(fragFile, GL_FRAGMENT_SHADER);

		//Create a new shader program
		program = glCreateProgram();

		//Compile the source code for each shader and attach it to the program.
		glCompileShader(vSource);
		printLog("vertex compile log: ", vSource);
		glAttachShader(program, vSource);

		glCompileShader(gSource);
		printLog("geometry compile log: ", gSource);
		glAttachShader(program, gSource);

		glCompileShader(fSource);
		printLog("fragment compile log: ", fSource);
		glAttachShader(program, fSource);

		//link all of the attached shader objects
		glLinkProgram(program);
	}


	/**
	* @param  label
	* @param  obj
	*/
	void printLog (string label, GLint obj )
	{       
		int infologLength = 0;
		int maxLength = 0;

		if(glIsShader(obj)) {
			glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
		} else {
			glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
		}

		char infoLog[128];

		if (glIsShader(obj)) {
			glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
		} else {
			glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);
		}

		if (infologLength > 0) {
			cerr << label << infoLog << endl;
		}
	}

public:

	GLint program;
	GLint modelViewLoc;
	GLint projectionLoc;
	GLint normalMatLoc;
	GLint vertexLoc;
	GLint normalLoc;
	GLuint vertexBuffer;
	GLuint normalBuffer;

	// Private attribute accessor methods
	//  

private:

public:


	// Private attribute accessor methods
	//  


	/**
	* Set the value of program
	* @param new_var the new value of program
	*/
	void setProgram ( GLint new_var )     {
		program = new_var;
	}

	/**
	* Get the value of program
	* @return the value of program
	*/
	GLint getProgram ( )     {
		return program;
	}

	/**
	* Set the value of modelViewLoc
	* @param new_var the new value of modelViewLoc
	*/
	void setModelViewLoc ( GLint new_var )     {
		modelViewLoc = new_var;
	}

	/**
	* Get the value of modelViewLoc
	* @return the value of modelViewLoc
	*/
	GLint getModelViewLoc ( )     {
		return modelViewLoc;
	}

	/**
	* Set the value of projectionLoc
	* @param new_var the new value of projectionLoc
	*/
	void setProjectionLoc ( GLint new_var )     {
		projectionLoc = new_var;
	}

	/**
	* Get the value of projectionLoc
	* @return the value of projectionLoc
	*/
	GLint getProjectionLoc ( )     {
		return projectionLoc;
	}

	/**
	* Set the value of normalMatLoc
	* @param new_var the new value of normalMatLoc
	*/
	void setNormalMatLoc ( GLint new_var )     {
		normalMatLoc = new_var;
	}

	/**
	* Get the value of normalMatLoc
	* @return the value of normalMatLoc
	*/
	GLint getNormalMatLoc ( )     {
		return normalMatLoc;
	}

	/**
	* Set the value of vertexLoc
	* @param new_var the new value of vertexLoc
	*/
	void setVertexLoc ( GLint new_var )     {
		vertexLoc = new_var;
	}

	/**
	* Get the value of vertexLoc
	* @return the value of vertexLoc
	*/
	GLint getVertexLoc ( )     {
		return vertexLoc;
	}

	/**
	* Set the value of normalLoc
	* @param new_var the new value of normalLoc
	*/
	void setNormalLoc ( GLint new_var )     {
		normalLoc = new_var;
	}

	/**
	* Get the value of normalLoc
	* @return the value of normalLoc
	*/
	GLint getNormalLoc ( )     {
		return normalLoc;
	}

	/**
	* Set the value of vertexBuffer
	* @param new_var the new value of vertexBuffer
	*/
	void setVertexBuffer ( GLuint new_var )     {
		vertexBuffer = new_var;
	}

	/**
	* Get the value of vertexBuffer
	* @return the value of vertexBuffer
	*/
	GLuint getVertexBuffer ( )     {
		return vertexBuffer;
	}

	/**
	* Set the value of normalBuffer
	* @param new_var the new value of normalBuffer
	*/
	void setNormalBuffer ( GLuint new_var )     {
		normalBuffer = new_var;
	}

	/**
	* Get the value of normalBuffer
	* @return the value of normalBuffer
	*/
	GLuint getNormalBuffer ( )     {
		return normalBuffer;
	}
private:


	void initAttributes ( ) ;

};

#endif // SHADER_H
