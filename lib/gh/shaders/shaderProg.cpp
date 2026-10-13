
#include <map>
#include <iostream>
#include <glad/glad.h>

#include <gh/shaders.hpp>
#include <gh/exceptions.hpp>

using namespace std;
using namespace exc::shaders;

ShaderProgram::ShaderProgram(std::map<ShaderType, std::vector<std::string>> sources) {
  id = glCreateProgram();
  if (!id) throw ShaderCreationError("Failed to create shader program");
  std::map<ShaderType, Shader> sha;
  for (auto& [type, paths] : sources) {
    sha[type] = Shader(type, paths);
    sha[type].compile();
    sha[type].attach(id);
  }

  int success;
  char infoLog[INFO_LOG_SIZE];
  glLinkProgram(id);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, INFO_LOG_SIZE, NULL, infoLog);
    throw ShaderProgramLinkingError("Failed to link shader program:\n" + std::string(infoLog));
  }
}

void ShaderProgram::use() {
  glUseProgram(id);
}

int ShaderProgram::getAttrLoc(const std::string& name) const {
  return glGetAttribLocation(id, name.c_str());
}

int ShaderProgram::getUniLoc(const std::string& name) const {
  return glGetUniformLocation(id, name.c_str());
}

// void ShaderProgram::destroy() noexcept {
//   glDeleteProgram(id);
// }

ShaderProgram::~ShaderProgram() noexcept {
  if (id != 0) {
    glDeleteProgram(id);
    id = 0;
  }
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
  id = other.id;
  other.id = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
  if (this != &other) {
    glDeleteProgram(id); // This deletes the current program if it exists
    id = other.id;
    other.id = 0;
  }
  return *this;
}