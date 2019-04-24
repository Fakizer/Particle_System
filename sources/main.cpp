#include "ParticleS.hpp"
#include <glew/glew.h>


int main(void) {

    OGL_manager     glman;
    OCL_manager     clman;
    GravityManager  gm(3);

    std::cout << glman << std::endl;
    std::cout << clman << std::endl;

    ParticleS & pat = ParticleS::instance(&glman, &clman, &gm);

    FPS_manager::start();

    glman.rend_img_win(&pat);

    return (0);
}
