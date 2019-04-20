#ifndef WINDOW_HPP
#define WINDOW_HPP

#define __gl3_h_

#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include "PS_errors.hpp"

class Window
{
public:
    Window();
    ~Window();

    GLFWwindow*     win;
    int             current_win_w;
    int             current_win_h;
};


#endif
