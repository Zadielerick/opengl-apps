#include "GLFWWindow.h"

int main() {
  GLFWWindow window(1920, 1080, "Test Window");
  window.glInit();
  glViewport(0, 0, 1920, 1080);

  for (int i = 0; i < 100; i++) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window.swapBuffers();
  }
  return 0;
}
