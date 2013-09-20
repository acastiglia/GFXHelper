/**
 * Utilities for redering with OpenGL
 *
 * author: Anthony Castiglia
 *
 * references:
 *   http://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/
 *   http://en.wikibooks.org/wiki/OpenGL_Programming
 */

#ifndef __GFX_H__
#define __GFX_H__
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <utility>

typedef std::pair<std::vector<GLfloat>, std::vector<GLushort> > GFXObject;

class GFXWindow {
private:
	int height, width;
	float r, g, b, a;
	std::vector<GFXObject> objects;
	const char* vshaderPath;
	const char* fshaderPath;
	GLuint vao;

	static const int COLOR_DEPTH = 8;
	static const int ALPHA_DEPTH = 8;
	static const int DEPTH_BUFFER_BITS = 0;
	static const int STENCIL_BUFFER_BITS = 0;
	static const int VERTEX_SIZE = 3;

	// Camera coordinates
	glm::vec3 eyepoint;
	glm::vec3 lookat;
	glm::vec3 up;

	glm::mat4 mvp;
	GLint uniform_mvp;

public:
	GFXWindow(int h, int w);
	void setBG(float r, float g, float b, float a);
	void setVertexShader(const char* path);
	void setFragmentShader(const char* path);
	void setCamera(glm::vec3 eyepoint, glm::vec3 lookat, glm::vec3 up);
	void addObject(GFXObject obj);
	GFXObject getObject(int ind);
	void init();
	void idle(glm::mat4 model_transform);
	void render();
	void createWindow();
	void quit(int exit_status);
};

#endif
