
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace managers
{

  namespace window
  {

    inline GLFWwindow* window = nullptr;

    void init(unsigned int width, unsigned int height, const char* name, bool resizable = false);
    void destroy();
    bool shouldClose();
    void update();
    void registerInputCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
    void close();
  }

}