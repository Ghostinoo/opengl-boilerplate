
#pragma once
#include "./base.hpp"

namespace exc::gl
{

class GLFWInitializationError : public base::AppError
{
  public:
    explicit GLFWInitializationError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::GLFW_INITIALIZATION_FAILED, loc)
    {}
};

class GLFWNotInitialized : public base::AppError
{
  public:
    explicit GLFWNotInitialized(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::GLFW_ISNT_INITIALIZED, loc)
    {}
};

class GLADInitializationError : public base::AppError
{
  public:
    explicit GLADInitializationError(
      const std::string& message,
      std::source_location loc = std::source_location::current()
    ) : base::AppError(message, base::GLAD_INITIALIZATION_FAILED, loc)
    {}
};

} // namespace exc