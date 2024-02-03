#pragma once
#include<bits/stdc++.h>
#include<GL/glew.h>
// Start ind, no of coordinates, size of coordinate, stride, normalized
struct VertexBufferElement {
  unsigned int type, count;
  bool normalized;
  static unsigned int GetSizeOfType(unsigned int type)  {
    if (type == GL_FLOAT)
      return 4;
    assert(0);
  }
};
class VertexBufferLayout {
  private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
  public:
    VertexBufferLayout() : m_Stride(0) {};
    template<typename T>
    void Push(unsigned int count) {
      __builtin_trap();
    }
    template<>
      void Push<float> (unsigned int count) {
        m_Elements.push_back({GL_FLOAT, count, false});
        m_Stride += sizeof(GLfloat) * count;
      }
    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
};
