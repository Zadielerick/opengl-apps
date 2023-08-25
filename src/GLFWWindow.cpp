#include "GLFWWindow.h"

static void errorCallback(int error, const char *description) {
  fputs(description, stderr);
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWWindow::GLFWWindow(uint32_t width, uint32_t height,
                       std::string windowName) {
  this->width = width;
  this->height = height;
  this->windowName = windowName;
}

int GLFWWindow::glInit() {
  glfwSetErrorCallback(errorCallback);
  if (!glfwInit()) {
    return -1;
  }

  this->window = glfwCreateWindow(this->width, this->height,
                                  this->windowName.c_str(), NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(this->window);
  glfwSetKeyCallback(window, keyCallback);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    glfwDestroyWindow(this->window);
    glfwTerminate();
    return -1;
  }

  return 0;
}

void GLFWWindow::swapBuffers() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();
}

int GLFWWindow::glDeinit() {
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
