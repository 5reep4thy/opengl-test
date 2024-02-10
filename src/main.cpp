#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float4.hpp"
#include "renderer.h"
#include "test.h"
#include "test_texture2d.h"
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
#include "tests/test_clear_color.h"

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

      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
      GLCall(glEnable(GL_BLEND));

      Renderer renderer;

      ImGui::CreateContext();
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui::StyleColorsDark();
      ImGui_ImplOpenGL3_Init("#version 330");
      test::Test* currentTest = nullptr;
      test::TestMenu* testMenu = new test::TestMenu(currentTest);
      currentTest = testMenu;
      testMenu->RegisterTest<test::TestClearColor> ("Clear Color");
      testMenu->RegisterTest<test::TestTexture2d>("Texture 2D");

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */
          renderer.Clear();
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();
  
          if (currentTest) {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if ((currentTest != testMenu) && ImGui::Button("<-")) {
              delete currentTest;
              currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
          }

          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();
      }
      delete currentTest;
      if (currentTest != testMenu)
        delete testMenu;

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
