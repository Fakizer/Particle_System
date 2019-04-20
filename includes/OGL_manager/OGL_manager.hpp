#ifndef OGL_MANAGER_HPP
#define OGL_MANAGER_HPP

#include <functional>
#include <vector>
#include <map>

#include "Window.hpp"
#include "PS_errors.hpp"
#include "Keyboard.hpp"
#include "ShaderHandler.hpp"

class ShaderHandler;

class OGL_manager
{
private:

    bool    initWindow();
    bool    initGLFW();
    bool    initGlew();
    void    createPrograms();

    Keyboard    keyboard;
    Window      window;
    // Shader      shader;

    std::function<void(void *)>		rend_func = nullptr;
    std::map<std::string, ShaderHandler *>	programs;
	std::vector<GLuint>						ubos;
	

public:
    OGL_manager();
    ~OGL_manager();
    
    void    rend_img_win();

};


#endif
