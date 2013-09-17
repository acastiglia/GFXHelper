/**
 * Utilities for redering with OpenGL
 *
 * author: Anthony Castiglia
 *
 * references:
 *   http://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/
 *   http://en.wikibooks.org/wiki/OpenGL_Programming
 */

#include <GL/glew.h>
#include <GL/glfw.h>
#include <vector>

class GFXWindow{
private:
	int height, width;
	float r, g, b, a;
	std::vector<std::vector<GLfloat> > objects;
	const char* vshaderPath;
	const char* fshaderPath;
	GLuint vao;

	static const int COLOR_DEPTH = 8;
	static const int ALPHA_DEPTH = 8;
	static const int DEPTH_BUFFER_BITS = 0;
	static const int STENCIL_BUFFER_BITS = 0;
	static const int VERTEX_SIZE = 3;

public:
	GFXWindow(int h, int w);
	void setBG(float r, float g, float b, float a);
	void setVertexShader(const char* path);
	void setFragmentShader(const char* path);
	void addObject(std::vector<GLfloat> vertices);
	std::vector<GLfloat> getObject(int ind);
	void init();
	void render();
	void createWindow();
	void quit(int exit_status);
};
