
#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "GLHelper.h"

void init() {
	const char* vSrc = load_shader_source("shaders/vshader.glsl");
	std::cout << vSrc << std::endl;

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vSrc, NULL);
	compile_shader(vshader);


	// const char* fSrc = load_shader_source("shaders/fshader.glsl");
	// std::cout << fSrc << std::endl;

	// GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(fshader, 1, &fSrc, NULL);
	// compile_shader(fshader);

}

void display() {
}

void quit(int exitStatus) {
	glfwTerminate();
	exit(exitStatus);
}

int main() {
	if (!glfwInit()) {
		log(ERROR, "Failed to initialize GLFW");
		exit(-1);
	}

	if (!glfwOpenWindow(600, 800, 8, 8, 8, 0, 0, 0, GLFW_WINDOW)) {
		log(ERROR, "GLFW failed to open window");
		quit(-1);
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		log(ERROR, "Failed to initialize GLEW");
		quit(-1);
	}

	init();

	quit(0);
}
