#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
class VertexArray {
  private:
    unsigned int m_Renderer_ID;
  public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void UnBind() const;
  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
