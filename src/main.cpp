#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<bits/stdc++.h>
#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

static void ParseShader(const std::string& filepath, std::string& vertexShader, std::string& fragmentShader) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;  
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;  
    }
        else
            ss[(int)type] << line << "\n";
        
    }
    vertexShader = ss[0].str();
    fragmentShader = ss[1].str();
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( result == GL_FALSE ) {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message = (char*)alloca(length * sizeof(char));
      glGetShaderInfoLog(id, length, &length, message);
      std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << message << std::endl;
      glDeleteShader(id);
      return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
         -0.5f, -0.5f,
          0.5f, -0.5f,
          0.5f,  0.5f,
          -0.5f, 0.5f
      };
      unsigned int indices[] = {
          0, 1, 2, 
          2, 3, 0
      };
      VertexArray va;
      VertexBuffer vb(positions, sizeof(float)* 4 * 2);

      VertexBufferLayout layout;
      layout.Push<float> (2);
      va.AddBuffer(vb, layout);


      IndexBuffer ib(indices, sizeof(unsigned int) * 6);

      std::string vertexShader, fragmentShader;
      ParseShader("res/shaders/basic.shader", vertexShader, fragmentShader);
      unsigned int shader = CreateShader(vertexShader, fragmentShader);
      glUseProgram(shader);
      int location = glGetUniformLocation(shader, "u_Color");
      ASSERT(location != -1);
      glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

      GLCall(glBindVertexArray(0));
      GLCall(glUseProgram(0));
      GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
      GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

      float r = 0.0f, increment = 0.01f;
      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */
          glClear(GL_COLOR_BUFFER_BIT);
          GLCall(glUseProgram(shader));
          glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
          if (r < 0.0f || r > 1.0f)
              increment = -increment;
          r += increment;
              
          va.Bind();
          ib.Bind();
         
          GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();
      }

      glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}
