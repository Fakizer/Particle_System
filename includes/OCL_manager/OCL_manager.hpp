#ifndef OCL_MANAGER_HPP
#define OCL_MANAGER_HPP

#define __gl3_h_

#include <OpenGL/CGLCurrent.h>
#include <glew/glew.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>
// #define __NO_STD_VECTOR // Use cl::vector instead of STL version
#define __CL_ENABLE_EXCEPTIONS

#ifdef __APPLE__
    // #include <OpenCL/cl.h> /* read cpp_wrapper_fix.txt */
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.h>
#endif

#include <CL/cl.hpp>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "OCL_manager.hpp"

class OCL_manager
{
private:

    cl::Platform                                platform;
    cl::Device                                  device;
	cl::Program::Sources	                    sources;

public:
    cl::Context				                    context;
    cl::Program                                 program;
	std::vector<cl::Memory>	                    vbos;
	cl::CommandQueue		                    queue;


    OCL_manager();
    ~OCL_manager();
    cl::Platform	    getPlatform(const std::string & defaultName);
    cl::Device  		getDevice(const cl::Platform & platform, const std::string & defaultName);
    static std::string	        getPlatformName(const cl::Platform & platform);
    static std::string	        getDeviceName(const cl::Device & device);
    int		promptChoice(const std::string & questionText, const std::string & answerText,
                            const std::vector<std::string> & choices);
    bool		        isAnswerCorrect(const std::vector<std::string> & choices, const std::string & answer);

    void    init_cl(const std::string & defPlatName, const std::string & defDevName);
    void    addKernelFiles(const std::string source);
    void    buildKernelProgram();

    cl::Platform        getPlatform() const;
    cl::Device             getDevice() const;
    cl::CommandQueue        getQueue();
};

std::ostream &		operator<<(std::ostream & os, const OCL_manager & cl);


#endif
