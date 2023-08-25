#include "Shader.h"
#include <iostream>

/* Shader Constructors */
Shader::Shader(GLenum shaderType) : shaderType(shaderType) {}
Shader::Shader(GLenum shaderType, std::string source)
    : shaderType(shaderType), source(std::move(source)) {}

/* Vertex Shader Constructors */
VertexShader::VertexShader() : Shader(GL_VERTEX_SHADER) {}
VertexShader::VertexShader(std::string source)
    : Shader(GL_VERTEX_SHADER, source) {}

/* Fragment Shader Constructors */
FragmentShader::FragmentShader() : Shader(GL_FRAGMENT_SHADER) {}
FragmentShader::FragmentShader(std::string source)
    : Shader(GL_FRAGMENT_SHADER, source) {}

/* Shader Program Constructor */
ShaderProgram::ShaderProgram(std::string vsSource, std::string fsSource)
    : vs(vsSource), fs(fsSource) {}

void Shader::compileShader() {
  if (shaderType != GL_FRAGMENT_SHADER && shaderType != GL_VERTEX_SHADER) {
    std::cout << " Shader: Shader Type not set to GL_FRAGMENT_SHADER or "
                 "GL_VERTEX_SHADER";
    std::cout << std::endl;
    return;
  }

  /* Create and compile shader source code */
  shader = glCreateShader(shaderType);
  if (shader) {
    GLint compiled = 0;
    const char *c_str = source.c_str();

    glShaderSource(shader, 1, &c_str, NULL);

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    /* Compilation error handling */
    if (!compiled) {
      GLint infoLen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
      if (infoLen) {
        char *buf = (char *)malloc(infoLen);
        if (buf) {
          glGetShaderInfoLog(shader, infoLen, NULL, buf);
          std::cout << "GL: Could not compile shader " << shaderType << ":"
                    << std::endl;
          std::cout << buf << std::endl;
          free(buf);
        }
      } else {
        char *buf = (char *)malloc(0x1000);
        if (buf) {
          glGetShaderInfoLog(shader, 0x1000, NULL, buf);
          std::cout << "GL: Could not compile shader " << shaderType << ":"
                    << std::endl;
          std::cout << buf << std::endl;
          free(buf);
        }
      }
      glDeleteShader(shader);
      shader = 0;
    }
  }
}

void ShaderProgram::compileShaderProgram() {
  vs.compileShader();
  fs.compileShader();

  program = glCreateProgram();

  if (program) {
    GLint linkStatus = GL_FALSE;

    glAttachShader(program, vs.getShader());
    glAttachShader(program, fs.getShader());
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
      GLint bufLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
      if (bufLength) {
        char *buf = (char *)malloc(bufLength);
        if (buf) {
          glGetProgramInfoLog(program, bufLength, NULL, buf);
          std::cout << "GL: Could not link program:" << std::endl;
          std::cout << buf << std::endl;
          free(buf);
        }
      }
      glDeleteProgram(program);
      program = 0;
    }
  }

  if (vs.getShader() && fs.getShader() && program) {
    glDeleteShader(vs.getShader());
    glDeleteShader(vs.getShader());
  }
}
