#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <sys/time.h>
#include <time.h>
#include "GFX.h"
#include "GFXUtil.h"

#define BILLION 1000000000L

// Cartesian basis vectors
const glm::vec3 e1(1.0, 0.0, 0.0);
const glm::vec3 e2(0.0, 1.0, 0.0);
const glm::vec3 e3(0.0, 0.0, 1.0);


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

std::vector<GLushort> faces_data
(faces, faces + sizeof(faces) / sizeof(GLushort));

GFXObject square(vertex_data, faces_data);

const double T_nsec = 20.0 * BILLION;
const float x_min = -1.0f;
const float x_max = 1.0f;
const float y_min = -1.0f;
const float y_max = 1.0f;
const float total_rotation = 360.0f;

glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(x_min, y_min, 0.0));
glm::vec3 eyepoint(0.0, 0.0, 4.0);
glm::vec3 lookat(0.0, 0.0, -1.0);
glm::vec3 up(0.0, 1.0, 0.0);

float v_x = (x_max - x_min) / T_nsec;
float v_y = (y_max - y_min) / T_nsec;
float rotational_velocity = total_rotation / T_nsec; // in deg/ns

GFXWindow gw(800, 800);

// void idle() {
// 	M = glm::translate(M, v_x * dt * e1 + v_y * dt * e2);
// 	gw.idle(M);
// 	gw.render();
// }

int main() {
  gw.setBG(0, 0, 0, 0);
  gw.setCamera(eyepoint, lookat, up);
  gw.addObject(square);

  gw.setVertexShader("shaders/vert.shader");
  gw.setFragmentShader("shaders/frag.shader");
  gw.createWindow();
  gw.init();

  int frames = 0;

  double x = x_min;
  double y = y_min;
  double theta = 0.0;
  double dx = 0.0;
  double dy = 0.0;
  double d_theta;
  double dt;
  double tt;

  struct timespec t0;
  struct timespec t1;
  struct timespec t2;
  struct timespec tf;
  clock_gettime(CLOCK_MONOTONIC, &t0);
  clock_gettime(CLOCK_MONOTONIC, &t1);

  do {

    clock_gettime(CLOCK_MONOTONIC, &t2);

    dt = (t2.tv_sec - t1.tv_sec) * BILLION + (t2.tv_nsec - t1.tv_nsec);
    dx = dt * v_x;
    dy = dt * v_y;
    x = x + dx;
    y = y + dy;
    d_theta = rotational_velocity * dt;
    theta = theta + d_theta;

    clock_gettime(CLOCK_MONOTONIC, &t1);

    glm::mat4 M_r = glm::rotate(glm::mat4(1.0f), (float) theta, e2);
    glm::mat4 M_t = glm::translate(glm::mat4(1.0f), (float) x * e1 + (float) y * e2);

    gw.idle(M_t * M_r);
    gw.render();
    frames++;

    clock_gettime(CLOCK_MONOTONIC, &tf);
    tt = (tf.tv_sec - t0.tv_sec) + (tf.tv_nsec - t0.tv_nsec) / BILLION;

    glfwPollEvents();
  } while (tt < 20.0 && glfwGetWindowParam(GLFW_OPENED));

  int total_time = tf.tv_sec - t0.tv_sec;
  double fps = (double) frames / (double) total_time;
  std::cout << "Summary: " << frames << " frames rendered in "
    << total_time << "s" << " (" << fps << "fps)" << std::endl;

  glfwTerminate();
}
