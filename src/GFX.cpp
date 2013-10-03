/**
 * Implementation file for GFX.h
 *
 * author: Anthony Castiglia
 */

#include "GFXUtil.h"
#include "GFX.h"

/* ---------------- GFXScene implementation ------------------------------ */

GFXScene::GFXScene() {
	if (!glfwGetWindowParam(GLFW_OPENED)) {
		log(WARNING, "Render context not detected");
		// quit(-1);
	} else {
		render_context_available = true;
	}
}

void GFXScene::setCamera(glm::vec3 eyepoint, glm::vec3 lookat, glm::vec3 up) {
  this->eyepoint = eyepoint;
  this->lookat = lookat;
  this->up = up;
}

void GFXScene::setBG(float r, float g, float b, float a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
  glClearColor(r, g, b, a);
}

void GFXScene::setVertexShader(const char* path) {
  vshaderPath = path;
}

void GFXScene::setFragmentShader(const char* path) {
  fshaderPath = path;
}

void GFXScene::addObject(GFXObject obj) {
  objects.push_back(obj);
}

GFXObject GFXScene::getObject(int ind) {
  return objects[ind];
}

void GFXScene::init() {
  if (!render_context_available) {
		log(WARNING, "Render context not detected");
  }

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    log(ERROR, "Failed to initialize GLEW");
    quit(-1);
  }

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GFXObject obj = getObject(0);
  std::vector<GLfloat> vertex_data = obj.first;
  std::vector<GLushort> faces_data= obj.second;

  // Create and bind the vertex buffer
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
      GL_ARRAY_BUFFER, 
      vertex_data.size() * sizeof(GLfloat), 
      &vertex_data[0], 
      GL_STATIC_DRAW);	

  // Create and bind the element (index) buffer
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(
      GL_ELEMENT_ARRAY_BUFFER, 
      faces_data.size() * sizeof(GLushort),
      &faces_data[0],
      GL_STATIC_DRAW);

  GLuint shaderProgram;

  try {
    shaderProgram = shader_program_from_files(vshaderPath, fshaderPath);
  } catch (const char* err) {
    log(ERROR, err);
    quit(-1);
  }

  uniform_mvp = glGetUniformLocation(shaderProgram, "mvp");

  if (uniform_mvp == -1) {
    log(ERROR, "Could not bind uniform variable 'mvp' in vertex shader");
    quit(-1);
  }

  GLint position_attribute = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(position_attribute, VERTEX_SIZE, GL_FLOAT, GL_FALSE, 
			0, 0);

  // Enable the attribute
  glEnableVertexAttribArray(position_attribute);
}

void GFXScene::render() {
  int size;

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindVertexArray(vao);
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);	
  glFlush();

  glfwSwapBuffers();
}

void GFXScene::idle(glm::mat4 model_transform, int width, int height) {
  glm::mat4 view = glm::lookAt(eyepoint, lookat, up);
  glm::mat4 projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f,
      10.0f);
  mvp = projection * view * model_transform;
  glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
}

/* ---------------- GFXWindow implementation ------------------------------- */

GFXWindow::GFXWindow(int h, int w) : height(h), width(w) {
    std::vector<std::vector<GLfloat> > objects;
}

std::pair<int, int> GFXWindow::getWindowDimensions() {
	return std::pair<int, int>(width, height);
}

void GFXWindow::createWindow() {
  if (!glfwInit()) {
    log(ERROR, "Failed to initialize GLFW");
    exit(-1);
  }

  if (!glfwOpenWindow(width, height, 
        COLOR_DEPTH, COLOR_DEPTH, COLOR_DEPTH, ALPHA_DEPTH, 
        DEPTH_BUFFER_BITS, STENCIL_BUFFER_BITS, GLFW_WINDOW)) {
    log(ERROR, "Failed to create GLFW window");
    quit(-1);
  }
}

void quit(int exit_status) {
  glfwTerminate();
  exit(exit_status);
}

