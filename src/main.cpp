#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<bits/stdc++.h>
#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // Problem: glewInit failed
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "GL version: %s\n", glGetString(GL_VERSION));
    {
      float positions[] = {
         -0.5f, -0.5f,
          0.5f, -0.5f,
          0.5f,  0.5f,
          -0.5f, 0.5f
      };
      unsigned int indices[] = {
          0, 1, 2, 
          2, 3, 0
      };
      VertexArray va;
      VertexBuffer vb(positions, sizeof(float)* 4 * 2);

      VertexBufferLayout layout;
      layout.Push<float> (2);
      va.AddBuffer(vb, layout);


      IndexBuffer ib(indices, sizeof(unsigned int) * 6);
      Shader shader("res/shaders/basic.shader");
      shader.Bind();
      shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

      shader.Unbind();
      va.UnBind();
      vb.Unbind();
      ib.Unbind();
      Renderer renderer;

      float r = 0.0f, increment = 0.01f;
      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */
          renderer.Clear();
          shader.Bind();
          shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
          if (r < 0.0f || r > 1.0f)
              increment = -increment;
          r += increment;
              
         
          renderer.Draw(va, ib, shader);

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();
      }

    }

    glfwTerminate();
    return 0;
}
