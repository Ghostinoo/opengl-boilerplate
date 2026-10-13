
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>

#include <gh/shaders.hpp>


enum class BufferDataType {
  FLOAT = GL_FLOAT,
  DOUBLE = GL_DOUBLE,
  BYTE = GL_BYTE,
  UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
  SHORT = GL_SHORT,
  UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  INT = GL_INT,
  UNSIGNED_INT = GL_UNSIGNED_INT,
  HALF_FLOAT = GL_HALF_FLOAT,
  FIXED = GL_FIXED,
  INT_PACKED = GL_INT_2_10_10_10_REV,
  UNSIGNED_INT_PACKED = GL_UNSIGNED_INT_2_10_10_10_REV  
};


class BaseBuffer
{
protected:
  unsigned int id;

public:
  explicit BaseBuffer();

  BaseBuffer(const BaseBuffer& other) = delete;
  BaseBuffer& operator=(const BaseBuffer& other) = delete;
  BaseBuffer(BaseBuffer&& other) noexcept;
  BaseBuffer& operator=(BaseBuffer&& other) noexcept;

  void uploadData(const void* data, size_t size, unsigned int usage) const;
  unsigned int getID() const { return id; }

  ~BaseBuffer();
};


class VBO : public BaseBuffer
{
public:
  struct Attribute {
    std::string name;
    BufferDataType type = BufferDataType::FLOAT;
    int count = 1; // range [1, 4]
    int location = -1;
    bool normalized = false;
    bool keepAsInteger = false;
  };

  explicit VBO(
    ShaderProgram& shaderProgram,
    const std::vector<Attribute>& attributes
  );

  void bindToVAO(unsigned int vaoID, unsigned int bindingIndex) const;
  void enableAttributes(unsigned int vaoID) const;

private:
  struct rawAttribute {
    int count;
    unsigned int type;
    bool normalized;
    unsigned int offset;
    unsigned int enablingFuncType; // range [0, 2]
      // 0 -> glVertexArrayAttribFormat
      // 1 -> glVertexArrayAttribIFormat
      // 2 -> glVertexArrayAttribLFormat
    unsigned int location;
  };

  std::vector<rawAttribute> attributes;
  int stride;
};


class EBO : public BaseBuffer
{
public:
  using BaseBuffer::BaseBuffer;
  void bindToVAO(unsigned int vaoID) const;
};


class VAO
{
private:
  unsigned int id;
  std::vector<VBO> vbos;
  EBO ebo;

public:

  struct BufferData {
    const void* data;
    size_t size;
    unsigned int usage;
  };

  struct VertexBufferConfig {
    std::vector<VBO::Attribute> attributes;
    BufferData bufferData;
  };

  explicit VAO(
    ShaderProgram& shaderProgram,
    const std::vector<VertexBufferConfig>& vboConstructors,
    const BufferData& eboData
  );
  ~VAO() noexcept;

  VAO(const VAO& other) = delete;
  VAO& operator=(const VAO& other) = delete;
  VAO(VAO&& other) noexcept;
  VAO& operator=(VAO&& other) noexcept;

  void bind() const { glBindVertexArray(id); }

  unsigned int getID() const { return id; }
  
  const EBO& getEBO() const { return ebo; }
  const std::vector<VBO>& getVBOs() const { return vbos; }
};