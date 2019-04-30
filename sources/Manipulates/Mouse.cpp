#include "Mouse.hpp"
#include "PS_errors.hpp"
#include "ParticleS.hpp"

bool        Mouse::mouse_enable = false;
glm::vec2   Mouse::current_pos;

void        Mouse::mouse_click_callback(GLFWwindow * window, int button, int action, int _) {
    if (mouse_enable && action == 1){
        ParticleS & ps = ParticleS::instance();
        if (!ps.pause) {
            Point * gp = ps.gm.getPointInPosFM(current_pos);
        }
    }
}

void        Mouse::mouse_move_callback(GLFWwindow * window, double x, double y) {

    current_pos = glm::vec2(static_cast<int>(x), static_cast<int>(y));
    if(mouse_enable) {
    }
}
