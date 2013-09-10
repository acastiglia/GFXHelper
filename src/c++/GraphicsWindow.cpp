#include "GraphicsWindow.h"
#include "util.h"

GraphicsWindow::GraphicsWindow(int h, int w): height(h), width(w) {
	setBG(0., 0., 0., 0.);
}

void GraphicsWindow::setBG(double r, double g, double b, double a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void GraphicsWindow::show() {
	if (!glfwGetWindowParam(GLFW_OPENED)) {
		this->createWindow();
	}

	glClearColor(r, g, b, a);
	int running = GL_TRUE;

	while (running) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers();
		glfwPollEvents();
		running = glfwGetWindowParam(GLFW_OPENED);
	}
}

void GraphicsWindow::createWindow() {
	if (!glfwInit()) {
		log(ERROR, "Failed to initialize GLFW");
		exit(-1);
	}

	if (!glfwOpenWindow(height, width, 8, 8, 8, 0, 0, 0, GLFW_WINDOW)) {
		log(ERROR, "GLFW failed to open window");
		quit(-1);
	}
}

void GraphicsWindow::quit(int exit_status) {
	glfwTerminate();
	exit(exit_status);
}

int main() {
	GraphicsWindow gw(600, 600);
	gw.setBG(1., 1., 1., 1.);
	gw.show();
	
	gw.quit(0);
}
