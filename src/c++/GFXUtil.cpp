/**
 * GLHelper -- utilities for creating OpenGL programs.
 *
 * author: Anthony Castiglia
 *
 * References:
 *   * http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
 *   * http://solarianprogrammer.com/2013/05/10/opengl-101-windows-osx-linux-getting-started/
 */

#include "util.h"

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

std::string read_file(const char* path) {
	std::ifstream file;
	file.open(path, std::ios::in);
	
	if (!file.is_open()) {
		exit(-1);
	}

	std::string s;
	std::string line;
	while (getline(file, line)) {
		s += line + "\n";
	}

	file.close();
	return s;
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
		
		throw &compileLog[0];
	}
}

GLuint shader_program(const char* vshaderSrc, const char* fshaderSrc) {
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vshader, 1, &vshaderSrc, NULL);
	compile_shader(vshader);

	glShaderSource(fshader, 1, &fshaderSrc, NULL);
	compile_shader(fshader);
	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vshader);
	glAttachShader(shaderProgram, fshader);
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	return shaderProgram;
}

GLuint shader_program_from_files(const char* vshaderPath, const char*
		fshaderPath) {
	
	if (vshaderPath == NULL) {
		throw "No vertex shader specified";
	}

	if (fshaderPath == NULL) {
		throw "No fragment shader specified";
	}

	std::string vshaderStr = read_file(vshaderPath);
	const char* vshaderSrc = vshaderStr.c_str();

	std::string fshaderStr = read_file(fshaderPath);
	const char* fshaderSrc = fshaderStr.c_str();

	return shader_program(vshaderSrc, fshaderSrc);
}

