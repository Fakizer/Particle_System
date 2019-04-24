#pragma once


#define __gl3_h_
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

class Keyboard
{

private:
    static bool        space_pressed;
public:
    // Keyboard();
    // Keyboard(Window const & win);
    // Keyboard() = default;
    // ~Keyboard();

    static void    key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    
};
