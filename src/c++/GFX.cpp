/**
 * Implementation file for GFX.h
 *
 * author: Anthony Castiglia
 */

#include "util.h"
#include "GFX.h"

GFXWindow::GFXWindow(int h, int w) : height(h), width(w), vshaderPath(0),
	fshaderPath(0) {
	std::vector<std::vector<GLfloat> > objects();
}

void GFXWindow::setBG(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void GFXWindow::setVertexShader(const char* path) {
	vshaderPath = path;
}

void GFXWindow::setFragmentShader(const char* path) {
	fshaderPath = path;
}

void GFXWindow::addObject(std::vector<GLfloat> vertices) {
	objects.push_back(vertices);
}

std::vector<GLfloat> GFXWindow::getObject(int ind) {
	return objects[ind];
}

void GFXWindow::createWindow() {
	if (!glfwInit()) {
		log(ERROR, "Failed to initialize GLFW");
		quit(-1);
	}

	if (!glfwOpenWindow(width, height, 
				COLOR_DEPTH, COLOR_DEPTH, COLOR_DEPTH, ALPHA_DEPTH, 
				DEPTH_BUFFER_BITS, STENCIL_BUFFER_BITS, GLFW_WINDOW)) {
		log(ERROR, "Failed to create GLFW window");
		quit(-1);
	}
}

void GFXWindow::init() {
	// Check for an open window w/ rendering context, create one
	// if there isn't one already open
	if (!glfwGetWindowParam(GLFW_OPENED)) {
		createWindow();
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		log(ERROR, "Failed to initialize GLEW");
		quit(-1);
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<GLfloat> vertex_data = getObject(0);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW);	

	GLuint shaderProgram;

	try {
		shaderProgram = shader_program_from_files(vshaderPath, fshaderPath);
	} catch (const char* err) {
		log(ERROR, err);
		quit(-1);
	}

	GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(position_attribute, VERTEX_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);
}

void GFXWindow::render() {
	glClearColor(r, g, b, a);

	do {
		log(DEBUG, "render loop");
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, objects[0].size() / VERTEX_SIZE);
		glfwSwapBuffers();
	} while (glfwGetWindowParam(GLFW_OPENED));
}

void GFXWindow::quit(int exit_status) {
	glfwTerminate();
	exit(exit_status);
}

