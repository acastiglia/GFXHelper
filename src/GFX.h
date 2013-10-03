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

class GFXScene {
  private:
    static const int COLOR_DEPTH = 8;
    static const int ALPHA_DEPTH = 8;
    static const int DEPTH_BUFFER_BITS = 0;
    static const int STENCIL_BUFFER_BITS = 0;
    static const int VERTEX_SIZE = 3;

    GLfloat r, g, b, a;
		GLuint vao;
		GLuint vbo;
		GLuint ibo;
		bool render_context_available;
    const char* vshaderPath;
    const char* fshaderPath;
    std::vector<GFXObject> objects;

    // Camera coordinates
    glm::vec3 eyepoint;
    glm::vec3 lookat;
    glm::vec3 up;

    glm::mat4 mvp;
    GLint uniform_mvp;

  public:
		GFXScene();
    void setCamera(glm::vec3 eyepoint, glm::vec3 lookat, glm::vec3 up);
    void setBG(float r, float g, float b, float a);
    void setVertexShader(const char* path);
    void setFragmentShader(const char* path);
    void addObject(GFXObject obj);
    GFXObject getObject(int ind);
    void init();
		void idle(glm::mat4 model_transform, int width, int height);
    void render();
		friend void quit(int exit_status);
};

class GFXWindow {
  private:
    int height, width;
    static const int COLOR_DEPTH = 8;
    static const int ALPHA_DEPTH = 8;
    static const int DEPTH_BUFFER_BITS = 0;
    static const int STENCIL_BUFFER_BITS = 0;
    static const int VERTEX_SIZE = 3;

  public:
    GFXWindow(int h, int w);
		std::pair<int, int> getWindowDimensions();
    void createWindow();
		friend void quit(int exit_status);
};

void quit(int exit_status);
#endif
