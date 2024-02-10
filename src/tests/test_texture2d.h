#pragma once
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"
#include "shader.h"
#include "test.h"
#include "glm/glm.hpp"
#include <memory>
namespace test {
  class TestTexture2d: public Test {
    public:
      TestTexture2d();
      ~TestTexture2d();
      void OnUpdate(float deltaTime) override;
      void OnRender() override;
      void OnImGuiRender() override;
    private:
      glm::vec3 m_translationA, m_translationB;
      std::unique_ptr<VertexArray> m_vao;
      std::unique_ptr<VertexBuffer> m_vb;
      std::unique_ptr<IndexBuffer> m_ibo;
      std::unique_ptr<Texture> m_texture;
      glm::mat4 m_proj, m_view;
    
      Shader m_shader;
  };

}
