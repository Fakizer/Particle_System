#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#define __gl3_h_
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

#include "PS_errors.hpp"
#include "Window.hpp"

class Keyboard
{

private:
    
    Window      win;

public:
    Keyboard();
    Keyboard(Window const & win);
    // Keyboard() = default;
    ~Keyboard();

    static void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    
};

#endif
