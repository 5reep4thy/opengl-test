#include "test_texture2d.h"
#include "index_buffer.h"
#include "renderer.h"
#include "test.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include <memory>

namespace test {
  TestTexture2d::TestTexture2d() :m_translationA(100, 0, 0 ), m_translationB(500, 0, 0), m_shader("res/shaders/basic.shader"), m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f)), m_view(glm::translate( glm::mat4(1.0f), glm::vec3(100, 0, 0))){
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
      
    
      m_vao = std::make_unique<VertexArray>();
      m_ibo = std::make_unique<IndexBuffer>(indices, 6);
      std::cout << "hh";
      m_vb = std::make_unique<VertexBuffer> (positions, sizeof(float)* 4 * 4);

      VertexBufferLayout layout;
      layout.Push<float> (2);
      layout.Push<float> (2);
      m_vao->AddBuffer(*m_vb, layout);

      IndexBuffer ib(indices, sizeof(unsigned int) * 6);

      Shader shader("res/shaders/basic.shader");
      shader.Bind();
      shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
      m_texture = std::make_unique<Texture>("res/textures/SJ.png");
      shader.SetUniform1i("u_Texture", 0);

  }
  TestTexture2d::~TestTexture2d() {
   GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
  }

  void TestTexture2d::OnUpdate(float deltaTime) {
  }
  void TestTexture2d::OnRender() {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    Renderer renderer;
    m_texture->Bind();
    glm::mat4 model = glm::translate( glm::mat4(1.0f), m_translationA);
    glm::mat4 mvp = m_proj * m_view * model ;
    {
      m_shader.Bind();
      m_shader.SetUniformMat4f("u_MVP", mvp);
      renderer.Draw(*m_vao, *m_ibo, m_shader);
    }
    {
      model = glm::translate( glm::mat4(1.0f), m_translationB);
      mvp = m_proj * m_view * model ;
      m_shader.SetUniformMat4f("u_MVP", mvp);
      renderer.Draw(*m_vao, *m_ibo, m_shader);
    }
  }
  void TestTexture2d::OnImGuiRender() {
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::SliderFloat2("Translation", &m_translationA.x, 0.0f, 400.0f);
                  
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  }
}
