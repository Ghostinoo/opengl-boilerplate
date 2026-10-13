
#pragma once

#include <stdexcept>
#include <string>
#include <source_location>


namespace exc::base
{


enum AppErrorCode {
  GLFW_INITIALIZATION_FAILED =    0x0000,
  GLFW_ISNT_INITIALIZED =         0x0001,

  GLAD_INITIALIZATION_FAILED =    0x0100,

  BUFFER_TYPE_NOT_SUPPORTED =     0x0200,
  INVALID_VERTEX_ATTRIBUTE =      0x0201,

  SHADER_CREATION_ERROR =         0x0300,
  SHADER_COMPILATION_ERROR =      0x0301,
  SHADER_PROGRAM_LINKING_ERROR =  0x0302,
  LOCATION_NOT_FOUND_IN_PROGRAM = 0x0303,

  TEXTURE_CREATION_ERROR =        0x0400,
};

class AppError : public std::runtime_error
{
private:
  AppErrorCode code;
  std::source_location location;

public:
  explicit AppError(
    const std::string& message,
    AppErrorCode code,
    std::source_location loc = std::source_location::current()
  )
    : std::runtime_error(message), code(code), location(loc)
  {}

  const std::source_location& getLocation() const noexcept
    { return location; }
  
  AppErrorCode getCode() const noexcept
    { return code; }

  std::string full_info() const
  {
    return (
      std::string(what()) +
      " [" + location.file_name() +
      ":" + std::to_string(location.line()) + "]"
    );
  }
};


} // namespace exc::base