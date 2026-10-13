
#pragma once
#include "./base.hpp"

namespace exc::shaders
{

class ShaderCreationError : public base::AppError
{
  public:
    explicit ShaderCreationError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::SHADER_CREATION_ERROR, loc)
    {}
};

class ShaderCompilationError : public base::AppError
{
  public:
    explicit ShaderCompilationError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::SHADER_COMPILATION_ERROR, loc)
    {}
};

class ShaderProgramLinkingError : public base::AppError
{
  public:
    explicit ShaderProgramLinkingError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::SHADER_PROGRAM_LINKING_ERROR, loc)
    {}
};

class LocationNotfoundInProgramError : public base::AppError
{
  public:
    explicit LocationNotfoundInProgramError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::LOCATION_NOT_FOUND_IN_PROGRAM, loc)
    {}
};

}