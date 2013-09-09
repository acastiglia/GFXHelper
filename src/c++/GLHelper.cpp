/**
 * GLHelper -- utilities for creating OpenGL programs.
 *
 * author: Anthony Castiglia
 *
 * References:
 *   * http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
 *   * http://solarianprogrammer.com/2013/05/10/opengl-101-windows-osx-linux-getting-started/
 */

#include "GLHelper.h"

void log(log_type t, const char* message) {
	switch (t) {
		case ERROR:
			std::cerr << "[Error] " << message << std::endl;
			break;
		case WARNING:
			std::cerr << "[Warning] " << message << std::endl;
			break;
		case DEBUG:
			std::cout << "[Debug] " << message << std::endl;
			break;
		default:
			log(ERROR, "Invalid log type");
			break;
	}
}

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
		std::cerr << "Error: could not open shader '" << shaderpath << "'" 
			<< std::endl;
		exit(1);
	}

	return shaderSrc;
}

void compile_shader(GLuint shader) {
	GLint compile_success;
	int logLen;

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);

	if (!compile_success) {
		log(ERROR, "Failed to compile shader");
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		
		std::vector<char> compileLog(logLen);
		glGetShaderInfoLog(shader, logLen, NULL, &compileLog[0]);
		log(ERROR, &compileLog[0]);

		exit(-1);
	}
}
