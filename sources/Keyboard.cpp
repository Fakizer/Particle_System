#include "Keyboard.hpp"

Keyboard::Keyboard() {}

Keyboard::Keyboard(Window const & win) : win(win) {}

void    Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cerr << "key_callback(" << window << ", " << key << ", " <<
        scancode << ", " << action << ", " << mode << ");" << std::endl;
    if (GLFW_RELEASE == action) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // animate = !animate;
    }
}

Keyboard::~Keyboard() {}
