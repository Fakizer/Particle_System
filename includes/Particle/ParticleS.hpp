#ifndef __42RUN_HPP__
# define __42RUN_HPP__

#define __gl3_h_

// #ifdef __APPLE__
//     #include <OpenCL/opencl.h>
// #else
//     #include <CL/cl.h>
// #endif 

#include <iostream>
// #include <glad/glad.h>
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#define MAX_SOURCE_SIZE 1000

#include "OGL_manager.hpp"
#include "OCL_manager.hpp"
#include "GravityManager.hpp"
#include "Camera.hpp"
#include "Updater.hpp"
#include "FPS_manager.hpp"
#include "Particle.hpp"


class Updater;

class ParticleS
{
private:

    void        setCLbuffers();
    void        setupPartBuffer();
    void        setupGPBuffer();
    void		updateGPBuffer() const;
    void        updateUniforms() const;
    void        create_camera();
    void        init();

   	bool			_paused = false;

    ParticleS( OGL_manager & glman_in, OCL_manager & clman_in, GravityManager & gm_in);
    ~ParticleS();

public:

    static ParticleS &	 instance(OGL_manager * glman_in = nullptr, OCL_manager * clman_in = nullptr, GravityManager * gm_in = nullptr);

    void        render();
    void        changePS();

    OGL_manager & glman;
    OCL_manager & clman;
    GravityManager & gm;
    Camera          camera;
	cl_uint				entries_count;
    cl::Kernel         kernel;

};





#endif
