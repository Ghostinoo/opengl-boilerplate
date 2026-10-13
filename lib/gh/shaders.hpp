
#pragma once

#include <map>
#include <vector>
#include <string>
#include <glad/glad.h>

#define MAX_PER_SHADER_SOURCES 64
#define INFO_LOG_SIZE 512


enum class ShaderType {
  VERTEX = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
  COMPUTE = GL_COMPUTE_SHADER,
  TESS_CONTROL = GL_TESS_CONTROL_SHADER,
  TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER
};


class Shader
{
private:
  unsigned int id = 0;
  bool compiled = false;
  unsigned int attachedTo = 0;
  ShaderType type = ShaderType(0);
  std::vector<std::string> sources;

public:
  Shader() = default;
  Shader(ShaderType shaderType, const std::vector<std::string> &toBeCompiledPaths);
  Shader(ShaderType shaderType, const std::string &path);
  ~Shader() noexcept;
  
  Shader (const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;
  Shader(Shader&&) noexcept;
  Shader& operator=(Shader&&) noexcept;

  unsigned int getID() const noexcept { return id; }
  void compile();
  void attach(unsigned int programID);
};


class ShaderProgram
{
private:
  unsigned int id = 0;

public:
  ShaderProgram(std::map<ShaderType, std::vector<std::string>> sources);
  ~ShaderProgram() noexcept;

  // Deleting copy
  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;
  // Declaring move
  ShaderProgram(ShaderProgram&&) noexcept;
  ShaderProgram& operator=(ShaderProgram&&) noexcept;

  void use();
  int getID() const noexcept { return id; }
  int getAttrLoc(const std::string& name) const;
  int getUniLoc(const std::string& name) const;
};