#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<bits/stdc++.h>
#include "glm/ext/vector_float4.hpp"
#include "renderer.h"
#include "texture.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
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
         -0.5f, -0.5f, 0.0f, 0.0f,
          0.5f, -0.5f, 1.0f, 0.0f,
          0.5f,  0.5f, 1.0f, 1.0f,
          -0.5f, 0.5f, 0.0, 1.0f
      };
      unsigned int indices[] = {
          0, 1, 2, 
          2, 3, 0
      };

      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
      GLCall(glEnable(GL_BLEND));

      VertexArray va;
      VertexBuffer vb(positions, sizeof(float)* 4 * 4);

      VertexBufferLayout layout;
      layout.Push<float> (2);
      layout.Push<float> (2);
      va.AddBuffer(vb, layout);

      IndexBuffer ib(indices, sizeof(unsigned int) * 6);
      glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -0.75f, 0.75f, -1.0f, 1.0f);

      Shader shader("res/shaders/basic.shader");
      shader.Bind();
      shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
      shader.SetUniformMat4f("u_MVP", proj);
      Texture texture("res/textures/SJ.png");
      texture.Bind();
      shader.SetUniform1i("u_Texture", 0);

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
