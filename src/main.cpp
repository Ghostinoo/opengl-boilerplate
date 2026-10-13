
#include <iostream>
#include <cmath>
#include <glad/glad.h>

#include <gh/exceptions.hpp>
#include <gh/shaders.hpp>
#include <gh/buffers.hpp>
#include <gh/helpers/managers.hpp>

using namespace std;

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

float vertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.2f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f
};
float colors[] = {
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f
};
unsigned int indices[] = {
  0, 1, 2
};



const std::vector<VAO::VertexBufferConfig> vboConfigs = {
  {
    .attributes = {
      { "aPos", BufferDataType::FLOAT, 3 },
    },
    .bufferData = { vertices, sizeof(vertices), GL_STATIC_DRAW }
  },
  {
    .attributes = {
      { "aColor", BufferDataType::FLOAT, 3 }
    },
    .bufferData = { colors, sizeof(colors), GL_STATIC_DRAW }
  }
};

const VAO::BufferData eboConfig = {
  indices, sizeof(indices), GL_STATIC_DRAW
};



int main()
{
  try {

    // Window initialization
    managers::window::init(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", false);

    // Shaders compilation
    ShaderProgram shaderProgram = ShaderProgram({
      {ShaderType::VERTEX, {"shaders/base.vert"}},
      {ShaderType::FRAGMENT, {"shaders/base.frag"}}
    });

    // Buffers setup
    VAO vao(shaderProgram, vboConfigs, eboConfig);

    // Render loop
    while (!managers::window::shouldClose())
    {
      // Rendering commands
      glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shaderProgram.use();
      vao.bind();
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

      // Swapping buffers and polling events
      managers::window::update();
    }

    // Cleanup
    // -------
    managers::window::destroy();

    return 0;

  } catch (const exc::base::AppError& e) {
    cerr << e.full_info() << endl;
    return -1;
  }
}