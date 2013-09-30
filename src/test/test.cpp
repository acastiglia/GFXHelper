// Draw four triangles on a red background

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include "GFX.h"
#include "GFXUtil.h"

GLfloat verts[] = {
	0.5, -0.5, 0.0,
	0.5,  0.5, 0.0,
 -0.5, -0.5, 0.0,
 -0.5,  0.5, 0.0,
};

std::vector<GLfloat> vertex_data
  (verts, verts + sizeof(verts) / sizeof(GLfloat));

GLushort faces[] = {
	0, 1, 2,
	1, 3, 2
};

int tickX;
int tickY;
bool running;
GFXWindow gw(600, 800);

std::vector<GLushort> faces_data
	(faces, faces + sizeof(faces) / sizeof(GLushort));

GFXObject square(vertex_data, faces_data);

glm::vec3 eyepoint(0.0, 0.0, 4.0);
glm::vec3 lookat(0.0, 0.0, -1.0);
glm::vec3 up(0.0, 1.0, 0.0);

// Cartesian basis vectors
glm::vec3 e1(1.0, 0.0, 0.0);
glm::vec3 e2(0.0, 1.0, 0.0);
glm::vec3 e3(0.0, 0.0, 1.0);

glm::mat4 model_transform(1.0f);

void GLFWCALL keyboard(int key, int action) {
	if (key == 'Q' && action == GLFW_PRESS) {
		running = false;
	} else if (key == 'S') {
		model_transform = glm::translate(model_transform, -0.1f * e2);
	} else if (key == 'W') {
		model_transform = glm::translate(model_transform, 0.1f * e2);
	} else if (key == 'A') {
		model_transform = glm::translate(model_transform, -0.1f * e1);
	} else if (key == 'D') {
		model_transform = glm::translate(model_transform, 0.1f * e1);
	} else if (key == 'R') {
		model_transform = glm::rotate(model_transform, 15.0f, e2);
	}
	gw.idle(model_transform);
	gw.render();
}

int main() {
	gw.setBG(0, 0, 0, 0);
	gw.setCamera(eyepoint, lookat, up);
	gw.addObject(square);

	gw.setVertexShader("shaders/vert.shader");
	gw.setFragmentShader("shaders/frag.shader");
	gw.createWindow();
	gw.init();

	running = true;

	gw.idle(model_transform);
	gw.render();

	glfwSetKeyCallback(keyboard);
	int frames = 0;

	do {
		glfwPollEvents();
		frames++;
	} while (running && glfwGetWindowParam(GLFW_OPENED));

	std::cout << frames << std::endl;
}
