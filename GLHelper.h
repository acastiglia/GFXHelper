#ifndef __GRAPHICSUTIL__ 
#define __GRAPHICSUTIL__

#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const char* load_shader_source(const char* shaderpath);
GLuint shader_program(const char* vshader, const char* fshader);

#endif
