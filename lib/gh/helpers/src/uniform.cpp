
#include <gh/helpers/uniform.hpp>
#include <gh/exceptions.hpp>

Uniform::Uniform(const std::string& name, const ShaderProgram& shaderProgram)
{
  loc = shaderProgram.getUniLoc(name);
}

template <typename T>
void Uniform::set(T value) const
{
  
}