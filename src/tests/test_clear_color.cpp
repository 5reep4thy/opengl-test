#include "test_clear_color.h"
#include "renderer.h"
#include "test.h"
#include "imgui.h"

namespace test {
  TestClearColor::TestClearColor()
  : m_ClearColor {0.2f, 0.3f, 0.2f, 1.0f} {
  }
  TestClearColor::~TestClearColor() {
    m_ClearColor[0] = 0.2f;
    m_ClearColor[1] = 0.3f;
    m_ClearColor[2] = 0.2f;
    m_ClearColor[3] = 1.0f;
    GLCall(glClearColor(m_ClearColor[0],m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
  }

  void TestClearColor::OnUpdate(float deltaTime) {
  }
  void TestClearColor::OnRender() {
    GLCall(glClearColor(m_ClearColor[0],m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
  }
  void TestClearColor::OnImGuiRender() {
    ImGui::ColorEdit4("Clear color", m_ClearColor);
  }
}
