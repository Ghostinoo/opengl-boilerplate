
#include <gh/helpers/managers.hpp>
#include <gh/exceptions.hpp>


void escapeKey(GLFWwindow *, int key, int, int action, int) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    managers::window::close();
  }
}


void managers::window::init(
  unsigned int width,
  unsigned int height,
  const char* name,
  bool resizable
) {
  if (window)
    throw exc::gl::GLFWInitializationError("Window manager is already initialized");
  if (!glfwInit())
    throw exc::gl::GLFWInitializationError("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

  window = glfwCreateWindow(
    width, height, name, NULL, NULL
  );

  if (!window) {
    glfwTerminate();
    throw exc::gl::GLFWInitializationError("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    destroy();
    throw exc::gl::GLADInitializationError("Failed to initialize GLAD");
  }

  registerInputCallback(escapeKey);
}

void managers::window::destroy() {
  if (!window) return;
  glfwDestroyWindow(window);
  glfwTerminate();
  window = nullptr;
}

bool managers::window::shouldClose() {
  if (!window) throw exc::gl::GLFWNotInitialized("Window manager is not initialized");
  return glfwWindowShouldClose(window);
}

void managers::window::update() {
  if (!window) throw exc::gl::GLFWNotInitialized("Window manager is not initialized");
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void managers::window::close() {
  if (!window) return;
  glfwSetWindowShouldClose(window, true);
}

void managers::window::registerInputCallback(void (*callback)(GLFWwindow* window , int key , int scancode, int action, int mods)) {
  if (!window) throw exc::gl::GLFWNotInitialized("Window manager is not initialized");
  glfwSetKeyCallback(window, callback);
}