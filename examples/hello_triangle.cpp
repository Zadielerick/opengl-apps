#include "GLFWWindow.h"
#include "Shader.h"

int main() {
  GLFWWindow window(1920, 1080, "Test Window");
  window.glInit();
    static const char vertexShaderSource[] =
    " attribute vec4 aVertexPosition;\n"
    " void main(void) { \n"
    "     gl_Position = aVertexPosition;\n"
    " } \n";

    static const char fragmentShaderSource[] =
    " void main(void) {\n"
    "     gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    " } \n";

    GLfloat vVertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

	ShaderProgram program(vertexShaderSource, fragmentShaderSource);
	program.compileShaderProgram();

    glUseProgram(program.getProgram());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    for(int i = 0; i < 100; i++)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
		window.swapBuffers();
    }

    return 0;
}
