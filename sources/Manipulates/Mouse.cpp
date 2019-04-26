#include "Mouse.hpp"
#include "PS_errors.hpp"
#include "ParticleS.hpp"

bool        Mouse::mouse_enable = false;

void        Mouse::mouse_click_callback(GLFWwindow * window, int button, int action, int _) {

}

void        Mouse::mouse_move_callback(GLFWwindow * window, double x, double y) {
    if (mouse_enable){
        ParticleS & ps = ParticleS::instance();
        if (!ps.pause) {
            printf("%d | %d\n", (int)x, (int)y);
            ps.gm.freeAllPoints();
            Point * gp = ps.gm.getDefaultPoint(glm::vec2((float)x, (float)y));
        }
    }
}
