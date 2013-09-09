#ifndef __GLHELPER
#define __GLHELPER

#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

enum log_type {ERROR, WARNING, DEBUG};

const char* load_shader_source(const char* shaderpath);
void compile_shader(GLuint shader);
GLuint shader_program(const char* vshader, const char* fshader);
GLuint shader_program_from_files(const char* vshaderpath, const char*
		fshaderpath);
void log(log_type t, const char* message);

#endif
