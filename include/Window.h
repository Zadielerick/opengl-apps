#ifndef _WINDOW_H_
#define _WINDOW_H_

/* Window Class
 * Handles the following tasks for OpenGL:
 * - Creates a window for the OpenGL context
 * - Provides a swap-buffer implementation to call in the rendering loop
 * - Cleans up the OpenGL context on completion
 *
 * In order to interface with different frameworks, different implementations
 * will be defined. The build infrastructure will take care of including the
 * correct windowing system
 */
class Window {
public:
  virtual int glInit() = 0;
  virtual void swapBuffers() = 0;
  virtual int glDeinit() = 0;
};
#endif /* _WINDOW_H_ */
