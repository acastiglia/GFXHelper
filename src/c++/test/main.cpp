// Draw four triangles on a red background

#include <GL/glew.h>
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

std::vector<GLushort> faces_data
	(faces, faces + sizeof(faces) / sizeof(GLushort));


GFXObject p(vertex_data, faces_data);

int main() {
	
	GFXWindow gw(600, 600);
	gw.setBG(0, 0, 0, 0);
	gw.addObject(p);

	gw.setVertexShader("shaders/vert.shader");
	gw.setFragmentShader("shaders/frag.shader");
	gw.createWindow();
	gw.init();
	gw.render();
}
