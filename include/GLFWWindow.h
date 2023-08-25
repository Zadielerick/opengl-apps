#ifndef _GLFWWINDOW_H_
#define _GLFWWINDOW_H_

#include <stdio.h>
#include <string>

#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFWWindow : public Window {
private:
  uint32_t width;
  uint32_t height;
  std::string windowName;
  GLFWwindow *window;

public:
  GLFWWindow(uint32_t width, uint32_t height, std::string windowName);
  int glInit();
  void swapBuffers();
  int glDeinit();
};

#endif /* _GLFWWINDOW_H_ */
