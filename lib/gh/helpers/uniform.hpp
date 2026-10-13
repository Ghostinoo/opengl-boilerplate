
#pragma once

#include <string>

#include <gh/shaders.hpp>

class Uniform
{
private:
  unsigned int loc;

public:
  Uniform(const std::string& name, const ShaderProgram& shaderProgram);

  template <typename T>
  void set(T value) const;
};

