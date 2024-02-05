#include "vertex_array.h"
#include "renderer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include <GL/glew.h>

VertexArray::VertexArray () {
  GLCall(glGenVertexArrays(1, &m_Renderer_ID));
}

VertexArray::~VertexArray () {
  GLCall(glDeleteVertexArrays(1, &m_Renderer_ID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.GetStride(), (void *)offset));
    offset += element.count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
  }
}

void VertexArray::Bind() const {
  GLCall(glBindVertexArray(m_Renderer_ID));
}
void VertexArray::UnBind() const {
  GLCall(glBindVertexArray(0));
}
