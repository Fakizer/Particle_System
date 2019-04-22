#ifndef OGL_MANAGER_HPP
#define OGL_MANAGER_HPP

#include <functional>
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
    void    createVO();
    void    setPartBuff();


    Keyboard    keyboard;
    Window      window;

    std::function<void(void *)>		rend_func = nullptr;
    std::map<std::string, ShaderHandler *>	programs;
	std::vector<GLuint>						ubos;
	
    GLuint			part_vbos;
    GLuint			part_vaos;
    GLuint			gp_vbos;
    GLuint			gp_vaos;

    std::vector<GLuint>     vbo; // 0 - particle 1 - gp
    std::vector<GLuint>     vao;

public:
    OGL_manager();
    ~OGL_manager();
    
    void    rend_img_win();

};


#endif
