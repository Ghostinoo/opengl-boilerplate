
#pragma once
#include "./base.hpp"

namespace exc::textures
{

class TextureCreationError : public base::AppError
{
  public:
    explicit TextureCreationError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::TEXTURE_CREATION_ERROR, loc)
    {}
};

}