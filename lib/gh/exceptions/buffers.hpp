
#pragma once
#include "./base.hpp"

namespace exc::buffers
{


class BufferTypeNotSupported : public base::AppError
{
  public:
    explicit BufferTypeNotSupported(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::BUFFER_TYPE_NOT_SUPPORTED, loc)
    {}
};

class InvalidVertexAttribute : public base::AppError
{
  public:
    explicit InvalidVertexAttribute(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::INVALID_VERTEX_ATTRIBUTE, loc)
    {}
};


}