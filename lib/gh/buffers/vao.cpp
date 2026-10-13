
#include <gh/buffers.hpp>

VAO::VAO(
  ShaderProgram& shaderProgram,
  const std::vector<VertexBufferConfig>& vboConstructors,
  const BufferData& eboData
) {
  glCreateVertexArrays(1, &id);
  unsigned int bindingIndex = 0;

  for (const auto& vbo : vboConstructors) {
    vbos.emplace_back(shaderProgram, vbo.attributes);
    VBO& vboRef = vbos.back();
    vboRef.uploadData(vbo.bufferData.data, vbo.bufferData.size, vbo.bufferData.usage);
    vboRef.bindToVAO(id, bindingIndex);
    vboRef.enableAttributes(id);
    bindingIndex++;
  }

  ebo.uploadData(eboData.data, eboData.size, eboData.usage);
  ebo.bindToVAO(id);
}

VAO::VAO(VAO&& other) noexcept
{
  id = other.id;
  other.id = 0;
}

VAO& VAO::operator=(VAO&& other) noexcept
{
  if (this != &other)
  {
    if (id != 0) glDeleteVertexArrays(1, &id);
    id = other.id;
    other.id = 0;
  }
  return *this;
}

VAO::~VAO()
{
  if (id != 0) {
    glDeleteVertexArrays(1, &id);
  }
}