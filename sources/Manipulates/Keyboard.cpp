#include "Keyboard.hpp"
#include "PS_errors.hpp"
#include "ParticleS.hpp"
// Keyboard::Keyboard() {}

// Keyboard::Keyboard(Window const & win) : win(win) {}

bool                Keyboard::space_pressed = false;
unsigned int        Keyboard::max_entries_count = 1500000;
unsigned int        Keyboard::min_entries_count = 0;
std::map<std::string, bool>  Keyboard::repeater;

void    Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cerr << "key_callback(" << window << ", " << key << ", " <<
        scancode << ", " << action << ", " << mode << ");" << std::endl;
    ParticleS & ps = ParticleS::instance();
    if (GLFW_RELEASE == action) {
        movement_key_release(key);
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (!ps.pause) {
            // Point * gp = ps.gm.getDefaultPoint(glm::vec2((float)ps.glman.window.current_win_w / 2, 
            //                                             (float)ps.glman.window.current_win_h / 2));
            Point * gp = ps.gm.getDefaultPoint(glm::vec2(60.f, 
                                                        60.f));
        }
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        ps.gm.freeAllPoints();
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        ps.pause = !ps.pause;
    }
    if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
        updateEntries_count(100000, ps);
    }
    if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
        updateEntries_count(-100000, ps);
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        updateFigure("initialize_cube", ps);
        // ps.current_figure = std::string("initialize_cube");
        // ps.entries_count_changed = true;
        // ps.pause = true;
        // ps.updateParams();
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        updateFigure("initialize_sphere", ps);
        // ps.current_figure = std::string("initialize_sphere");
        // ps.entries_count_changed = true;
        // ps.pause = true;
        // ps.updateParams();
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        Mouse::mouse_enable = !Mouse::mouse_enable;
        ps.pause = !ps.pause;
    }
    movement(key, action);
    moveCamera(ps);    
}

void    Keyboard::movement(int key, int action) {
    if (action > 0)
        movement_key_press(key);
    if (action == 0)
        movement_key_release(key);
}

void    Keyboard::movement_key_press(int key) {
    if (key == GLFW_KEY_W) {
        repeater["forward"] = true;
    }
    else if (key == GLFW_KEY_S) {
        repeater["back"] = true;
    }
    else if (key == GLFW_KEY_D) {
        repeater["right"] = true;
    }
    else if (key == GLFW_KEY_A) {
        repeater["left"] = true;
    }
    else if (key == GLFW_KEY_Q) {
        repeater["up"] = true;
    }
    else if (key == GLFW_KEY_E) {
        repeater["down"] = true;
    }
}

void    Keyboard::movement_key_release(int key) {
    if (key == GLFW_KEY_W) {
        repeater["forward"] = false;
    }
    else if (key == GLFW_KEY_S) {
        repeater["back"] = false;
    }
    else if (key == GLFW_KEY_D) {
        repeater["right"] = false;
    }
    else if (key == GLFW_KEY_A) {
        repeater["left"] = false;
    }
    else if (key == GLFW_KEY_Q) {
        repeater["up"] = false;
    }
    else if (key == GLFW_KEY_E) {
        repeater["down"] = false;
    }
}

void    Keyboard::updateEntries_count(const int count, ParticleS & ps) {
    printf("%d\n", count);
    if (ps.entries_count + count < min_entries_count || ps.entries_count + count > max_entries_count)
        return;
    ps.entries_count += count;
    ps.pause = true;
    ps.entries_count_changed = true;
    Mouse::mouse_enable = false;
    ps.updateParams();
}

void     Keyboard::updateFigure(const std::string figure, ParticleS & ps) {
    ps.current_figure = figure;
    ps.entries_count_changed = true;
    ps.pause = true;
    Mouse::mouse_enable = false;
    ps.updateParams();
}

void    Keyboard::moveCamera(ParticleS & ps) {
    static std::clock_t	lastTime = std::clock();
	std::clock_t		newTime;
	cl_float			deltaTime;
    glm::vec3           direction(0.0f);

    if (repeater["forward"] == true) {
        direction = ps.camera.cf;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    if (repeater["back"] == true) {
        direction = -ps.camera.cf;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    if (repeater["right"] == true) {
        direction = ps.camera.cr;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    if (repeater["left"] == true) {
        direction = -ps.camera.cr;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    if (repeater["up"] == true) {
        direction = ps.camera.cu;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    if (repeater["down"] == true) {
        direction = -ps.camera.cu;
        ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
    }
    
    newTime = std::clock();
    deltaTime = 1000.f * (newTime - lastTime) / CLOCKS_PER_SEC;
    lastTime = newTime;
    // ps.camera.camPos += direction * ps.camera.speed / FPS_manager::fps;
}

// Keyboard::~Keyboard() {}
