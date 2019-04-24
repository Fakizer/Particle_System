#include "Keyboard.hpp"
#include "PS_errors.hpp"
#include "ParticleS.hpp"
// Keyboard::Keyboard() {}

// Keyboard::Keyboard(Window const & win) : win(win) {}

bool        Keyboard::space_pressed = false;

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
        ParticleS & ps = ParticleS::instance();
        Point * gp = ps.gm.getDefaultPoint(glm::vec2(ps.glman.window.current_win_w, ps.glman.window.current_win_h));
        space_pressed = true;
    }
    // if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && space_pressed) {
    //     ParticleS & ps = ParticleS::instance();
    //     ps.gm.freeAllPoints();
    //     space_pressed = false;
    // }
}

// Keyboard::~Keyboard() {}
