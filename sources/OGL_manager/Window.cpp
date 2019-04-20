#include "Window.hpp"

Window::Window() {
    this->win = nullptr;
    this->current_win_w = 1280;
    this->current_win_h = 1024;
}

Window::~Window() {
	glfwTerminate();
}
