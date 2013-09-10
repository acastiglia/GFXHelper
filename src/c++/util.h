#ifndef __GLHELPER
#define __GLHELPER

#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

enum log_type {ERROR, WARNING, DEBUG};

// GLuint shader_program_from_files(const char* vshaderpath, const char*
// 		fshaderpath);

void compile_shader(GLuint shader);
GLuint shader_program(const char* vshaderSrc, const char* fshaderSrc);

std::string read_file(const char* path);
void log(log_type t, const char* message);

#endif
