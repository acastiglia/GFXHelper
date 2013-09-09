/**
 * GLHelper -- utilities for creating OpenGL programs.
 *
 * author: Anthony Castiglia
 */

#include "GLHelper.h"

const char* load_shader_source(const char* shaderpath) {
	std::string shaderStr;
	const char* shaderSrc;

	std::ifstream shaderfile(shaderpath, std::ios::in);
	std::stringstream filebuffer;

	if (shaderfile.is_open()) {
		filebuffer << shaderfile.rdbuf(); // Dump the file into filebuffer
		shaderStr = filebuffer.str();     // Get the filebuffer's string
		shaderSrc = shaderStr.c_str();    // Convert to C-style string
		shaderfile.close();
	} else {
		std::cerr << "Error: could not open vertex shader '" << shaderpath << "'" 
			<< std::endl;
		exit(1);
	}

	return shaderSrc;
}

GLuint shader_program(const char* vshaderSrc, const char* fshaderSrc) {
	// Create shader objects
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	// Compile shaders
	glShaderSource(vshader, 1, &vshaderSrc, NULL);
	glCompileShader(vshader);

	glShaderSource(fshader, 1, &fshaderSrc, NULL);
	glCompileShader(fshader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vshader);
	glAttachShader(shaderProgram, fshader);

	return shaderProgram;	
}

GLuint shader_program_from_files(const char* vshaderpath, const char*
		fshaderpath) {
	const char* vshaderSrc = load_shader_source(vshaderpath);
	const char* fshaderSrc = load_shader_source(fshaderpath);
	return shader_program(vshaderSrc, fshaderSrc);
}

