#ifndef PS_ERRRORS_HPP
#define PS_ERRRORS_HPP

#include <exception>

struct PS_errors
{
    struct GLFW_init : public std::exception { char const * what( void ) const _NOEXCEPT; };
    struct Win_init : public std::exception { char const * what( void ) const _NOEXCEPT; };
    struct Glew_init : public std::exception { char const * what( void ) const _NOEXCEPT; };
};

#endif
