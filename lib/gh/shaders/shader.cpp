
#include <iostream>
#include <fstream>
#include <filesystem>

#include <gh/shaders.hpp>
#include <gh/exceptions.hpp>

using namespace std;
using namespace exc::shaders;


Shader::Shader(ShaderType shaderType, const vector<std::string> &toBeCompiledPaths) {
  type = shaderType;
  id = glCreateShader(static_cast<unsigned int>(type));
  if (id == 0) throw ShaderCreationError("Failed to create shader.");

  vector<const char*> ptrs;

  for (const auto& path : toBeCompiledPaths) {
    try {

      std::string content(std::filesystem::file_size(path), '\0');
      std::ifstream(path).read(content.data(), content.size());
      sources.emplace_back(content);
      ptrs.push_back(sources.back().c_str());

    } catch (const std::exception& e) {
      glDeleteShader(id);
      throw ShaderCreationError("Unexpected error while reading shader file " + path + ": " + e.what());
    }
  }
  
  glShaderSource(id, ptrs.size(), ptrs.data(), NULL);
}

Shader::Shader(ShaderType shaderType, const std::string &path)
  : Shader(shaderType, vector<std::string>{path})
{}

void Shader::attach(unsigned int programID) {
  glAttachShader(programID, id);
  attachedTo = programID;
}

Shader::Shader(Shader&& other) noexcept {
  id = other.id;
  compiled = other.compiled;
  attachedTo = other.attachedTo;
  type = other.type;
  sources = std::move(other.sources);

  other.id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
  if (this != &other) {
    if (id != 0) { // Delete current shader if it exists
      if (attachedTo) glDetachShader(attachedTo, id);
      glDeleteShader(id);
    }

    id = other.id;
    compiled = other.compiled;
    attachedTo = other.attachedTo;
    type = other.type;
    sources = std::move(other.sources);

    other.id = 0;
  }
  return *this;
}

void Shader::compile() {
  int success;
  char infoLog[INFO_LOG_SIZE];
  glCompileShader(id);
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(id, INFO_LOG_SIZE, NULL, infoLog);
    throw ShaderCompilationError("Failed to compile shader:\n" + std::string(infoLog));
  }

  compiled = true;
}

Shader::~Shader() noexcept {
  if (id == 0) return;
  if (attachedTo) glDetachShader(attachedTo, id);
  glDeleteShader(id);
}