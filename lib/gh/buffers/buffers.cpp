
#include <gh/buffers.hpp>
#include <gh/exceptions.hpp>

using namespace std;

BaseBuffer::BaseBuffer()
{
  glCreateBuffers(1, &id);
}

BaseBuffer::~BaseBuffer()
{
  if (id != 0) {
    glDeleteBuffers(1, &id);
  }
}

BaseBuffer::BaseBuffer(BaseBuffer&& other) noexcept
{
  id = other.id;
  other.id = 0;
}

BaseBuffer& BaseBuffer::operator=(BaseBuffer&& other) noexcept
{
  if (this != &other)
  {
    if (id != 0) glDeleteBuffers(1, &id);
    id = other.id;
    other.id = 0;
  }
  return *this;
}

void BaseBuffer::uploadData(const void* data, size_t size, unsigned int usage) const
{
  glNamedBufferData(id, size, data, usage);
}


// EBO Buffers
// -----------

void EBO::bindToVAO(unsigned int vaoID) const
{
  glVertexArrayElementBuffer(vaoID, id);
}