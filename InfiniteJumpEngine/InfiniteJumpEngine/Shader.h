#pragma once
#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include "glIncludes.h"

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
	* reads and compiles a vertex and fragment shader
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
		cout << "compiling shader " + vertFile << endl;
		glCompileShader(vSource);
		printLog("vertex shader: ", vSource);
		glAttachShader(program, vSource);
		
		cout << "compiling shader " + fragFile << endl;
		glCompileShader(fSource);
		printLog("fragment shader: ", fSource);
		glAttachShader(program, fSource);

		//link all of the attached shader objects
		glLinkProgram(program);
	}

	/**
	* parses the shader source
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
	* reads and compiles a vertex fragment and geometry shader files
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
		cout << "compiling shader " + vertFile << endl;
		glCompileShader(vSource);
		printLog("vertex shader: ", vSource);
		glAttachShader(program, vSource);
		
		cout << "compiling shader " + geomFile << endl;
		glCompileShader(gSource);
		printLog("geometry shader: ", gSource);
		glAttachShader(program, gSource);
		
		cout << "compiling shader " + fragFile << endl;
		glCompileShader(fSource);
		printLog("fragment shader: ", fSource);
		glAttachShader(program, fSource);

		//link all of the attached shader objects
		glLinkProgram(program);
	}


	/**
	* prints shader compile error log
	* @param  label
	* @param  obj
	*/
	void printLog (string label, GLint obj )
	{       

		GLint  compiled;
		glGetShaderiv( obj, GL_COMPILE_STATUS, &compiled );
		if ( !compiled ) {
			std::cerr << label << " failed to compile:" << std::endl;
			GLint  logSize;
			glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &logSize );
			char* logMsg = new char[logSize];
			glGetShaderInfoLog( obj, logSize, NULL, logMsg );
			std::cerr << logMsg << std::endl;
			delete [] logMsg;

			exit( EXIT_FAILURE );
		}
	}

public:

	GLint program;
	GLint modelViewLoc;
	GLint projectionLoc;
	GLint viewLoc;
	GLint normalMatLoc;
	GLint lightPosLoc;
	GLint vertexLoc;
	GLint normalLoc;
	GLint texCoordLoc;
	GLint colorLoc;
	GLint textureLoc;
	GLuint vertexBuffer;
	GLuint texCoordBuffer;
	GLuint normalBuffer;
	GLuint colorBuffer;

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

#endif SHADER_H
