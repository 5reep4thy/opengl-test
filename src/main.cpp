#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float4.hpp"
#include "renderer.h"
#include "texture.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);
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
          200.0f, 200.0f, 0.0f, 0.0f,
          400.0f, 200.0f, 1.0f, 0.0f,
          400.0f,  400.0f, 1.0f, 1.0f,
          200.0f, 400.0f, 0.0, 1.0f
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
      glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
      glm::mat4 view = glm::translate( glm::mat4(1.0f), glm::vec3(100, 0, 0));
      Shader shader("res/shaders/basic.shader");
      shader.Bind();
      shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
      Texture texture("res/textures/SJ.png");
      texture.Bind();
      shader.SetUniform1i("u_Texture", 0);

      shader.Unbind();
      va.UnBind();
      vb.Unbind();
      ib.Unbind();
      Renderer renderer;

      ImGui::CreateContext();
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui::StyleColorsDark();
      const char* glsl_version = "#version 330";
      ImGui_ImplOpenGL3_Init(glsl_version);

      ImGuiIO& io = ImGui::GetIO(); (void)io;
      glm::vec3 translationA(100, 0, 0), translationB(500, 0, 0);
      float r = 0.0f, increment = 0.01f;
      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */
          renderer.Clear();
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();
          glm::mat4 model = glm::translate( glm::mat4(1.0f), translationA);
          glm::mat4 mvp = proj * view * model ;
          {
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            renderer.Draw(va, ib, shader);
          }
          {
            model = glm::translate( glm::mat4(1.0f), translationB);
            mvp = proj * view * model ;
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
          }


          if (r < 0.0f || r > 1.0f)
              increment = -increment;
          r += increment;
              

          // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
          {

              ImGui::Begin("OpenGL");                          
              ImGui::SliderFloat2("Translation", &translationA.x, 0.0f, 400.0f);
                          
              ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
              ImGui::End();
          }
         

          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();
      }

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
