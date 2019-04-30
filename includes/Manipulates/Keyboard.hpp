#pragma once


#define __gl3_h_
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.hpp"
#include <map>
class ParticleS;

class Keyboard
{

private:
    static bool        space_pressed;
    static unsigned int max_entries_count;
    static unsigned int min_entries_count;
    struct KeyAction
    {
        int     front;
        int     right;
        int     up;
    };
    
public:
    static std::map<std::string, bool>  repeater_qweasd;
    static std::map<std::string, bool>  repeater_arrows;
    // Keyboard();
    // Keyboard(Window const & win);
    // Keyboard() = default;
    // ~Keyboard();

    static void     key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void     updateEntries_count(const int count, ParticleS & ps);
    static void     updateFigure(const std::string figure, ParticleS & ps);
    static void     movement(int key, int action);
    static void     movement_key_press_QWEASD(int key);
    static void     movement_key_release_QWEASD(int key);
    static void     movement_key_press_ARROWS(int key);
    static void     movement_key_release_ARROWS(int key);
};
