#pragma once

#define __gl3_h_
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

class ParticleS;

class Mouse
{
private:

public:

    static bool     mouse_enable;


    static void     mouse_click_callback(GLFWwindow * window, int button, int action, int _);
    static void     mouse_move_callback(GLFWwindow * window, double x, double y);
};
