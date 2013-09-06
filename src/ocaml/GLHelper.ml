(* GLHelper
 *
 * Utilites for OpenGL programming
 *
 * References:
 *   http://www.linux-nantes.org/~fmonnier/ocaml/GL/ocaml-opengl-howto-fc.php#def_bindings
 *)

open GL

let load_shaders vshaderSrc fshaderSrc = 
  let vshader = glCreateShader GL_VERTEX_SHADER in
  let fshader = glCreateShader GL_FRAGMENT_SHADER in
    glShaderSource vshader vshaderSrc;
    glShaderSource fshader fshaderSrc;
    glCompileShader vshader;
    glCompileShader fshader;

  let shaderProgram = glCreateProgram () in
    glAttachShader shaderProgram vshader;
    glAttachShader shaderProgram fshader;
    glLinkProgram shaderProgram;

    shaderProgram
  
