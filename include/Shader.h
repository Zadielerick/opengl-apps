#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <vector>

#include <GL/glew.h>

/* Shader Class
 * Handles the following tasks for OpenGL:
 * - GLSL shader compilation and error reporting
 * - OpenGL shader program
 */
class Shader {
protected:
  GLenum shaderType;
  GLuint shader;
  std::string source;

public:
  Shader(GLenum shaderType);
  Shader(GLenum shaderType, std::string source);
  GLenum getShaderType() { return shaderType; }
  GLuint getShader() { return shader; }
  void compileShader();
};

/* Vertex Shader Class */
class VertexShader : public Shader {
public:
  VertexShader();
  VertexShader(std::string source);
};

/* Fragment Shader Class */
class FragmentShader : public Shader {
public:
  FragmentShader();
  FragmentShader(std::string source);
};

/* Shader Program Class
 * Composition of a Vertex Shader and Fragment Shader for compiling the linked
 * program
 */
class ShaderProgram {
  VertexShader vs;
  FragmentShader fs;
  GLuint program;

public:
  ShaderProgram(std::string vsSource, std::string fsSource);
  void compileShaderProgram();
  GLuint getProgram() { return program; }
};
#endif /* _SHADER_H_ */
