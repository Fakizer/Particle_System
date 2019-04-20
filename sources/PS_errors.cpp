#include "PS_errors.hpp"

char const * PS_errors::GLFW_init::what( void ) const _NOEXCEPT {
    return "Error init GLFW";
}

char const * PS_errors::Win_init::what( void ) const _NOEXCEPT {
    return "Error init GLFWwindow";
}

char const * PS_errors::Glew_init::what( void ) const _NOEXCEPT {
    return "Error init Glew";
}
