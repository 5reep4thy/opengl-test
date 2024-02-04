#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "vertex_buffer_layout.h"
#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
  public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
