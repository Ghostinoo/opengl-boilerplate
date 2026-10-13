
#include <glad/glad.h>
#include <iostream>

#include <gh/buffers.hpp>
#include <gh/exceptions.hpp>

using namespace std;

VBO::VBO(ShaderProgram& shaderProgram, const std::vector<Attribute>& attributes)
{
  unsigned int offset = 0;
  for (const auto& attr : attributes)
  {
    if (attr.count < 1 || attr.count > 4)
      throw exc::buffers::InvalidVertexAttribute("Attribute count must be in range [1, 4]");
    rawAttribute rawAttr;
    rawAttr.count = attr.count;
    rawAttr.normalized = attr.normalized;
    rawAttr.type = static_cast<unsigned int>(attr.type);
    rawAttr.offset = offset;
    rawAttr.location = shaderProgram.getAttrLoc(attr.name);
    switch (attr.type)
    {
      case BufferDataType::FLOAT:
      case BufferDataType::HALF_FLOAT:
      case BufferDataType::FIXED:
      case BufferDataType::INT_PACKED:
      case BufferDataType::UNSIGNED_INT_PACKED:
        rawAttr.enablingFuncType = 0;
        break;
      case BufferDataType::DOUBLE:
        rawAttr.enablingFuncType = 2;
        break;
      case BufferDataType::BYTE:
      case BufferDataType::UNSIGNED_BYTE:
      case BufferDataType::SHORT:
      case BufferDataType::UNSIGNED_SHORT:
      case BufferDataType::INT:
      case BufferDataType::UNSIGNED_INT:
        rawAttr.enablingFuncType = (attr.keepAsInteger ? 1 : 0);
        break;
      default:
        throw exc::buffers::BufferTypeNotSupported("Unsupported buffer data type");
    }

    this->attributes.push_back(rawAttr);

    switch (attr.type)
    {
      case BufferDataType::FLOAT:
        offset += attr.count * sizeof(float);
        break;
      case BufferDataType::DOUBLE:
        offset += attr.count * sizeof(double);
        break;
      case BufferDataType::BYTE:
      case BufferDataType::UNSIGNED_BYTE:
        offset += attr.count * sizeof(unsigned char);
        break;
      case BufferDataType::SHORT:
      case BufferDataType::UNSIGNED_SHORT:
      case BufferDataType::HALF_FLOAT:
        offset += attr.count * sizeof(unsigned short);
        break;
      case BufferDataType::INT:
      case BufferDataType::UNSIGNED_INT:
      case BufferDataType::FIXED:
      case BufferDataType::INT_PACKED:
      case BufferDataType::UNSIGNED_INT_PACKED:
        offset += attr.count * sizeof(unsigned int);
        break;
      default:
        throw exc::buffers::BufferTypeNotSupported("Unsupported buffer data type");
    }
  }
  stride = offset;
}

void VBO::bindToVAO(unsigned int vaoID, unsigned int bindingIndex) const
{
  glVertexArrayVertexBuffer(vaoID, bindingIndex, id, 0, stride);
  for (const auto& attr : attributes)
  {
    switch (attr.enablingFuncType)
    {
      case 0:
        glVertexArrayAttribFormat(vaoID, attr.location, attr.count, attr.type, attr.normalized, attr.offset);
        glVertexArrayAttribBinding(vaoID, attr.location, bindingIndex);
        break;
      case 1:
        glVertexArrayAttribIFormat(vaoID, attr.location, attr.count, attr.type, attr.offset);
        glVertexArrayAttribBinding(vaoID, attr.location, bindingIndex);
        break;
      case 2:
        glVertexArrayAttribLFormat(vaoID, attr.location, attr.count, attr.type, attr.offset);
        glVertexArrayAttribBinding(vaoID, attr.location, bindingIndex);
        break;
    }
  }
}

void VBO::enableAttributes(unsigned int vaoID) const
{
  for (const auto& attr : attributes)
  {
    glEnableVertexArrayAttrib(vaoID, attr.location);
  }
}