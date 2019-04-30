#ifndef OGL_MANAGER_HPP
#define OGL_MANAGER_HPP

#include <functional>
#include <map>

#include "Window.hpp"
#include "PS_errors.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
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



	std::vector<GLuint>						ubos;
	
    // GLuint			part_vbos;
    // GLuint			part_vaos;
    // GLuint			gp_vbos;
    // GLuint			gp_vaos;


public:
    OGL_manager();
    ~OGL_manager();

    Mouse       mouse;
    Keyboard    keyboard;
    Window      window;
    
    void    rend_img_win(void * prog);

    std::function<void(void *)>		rend_func = nullptr;

    std::map<std::string, ShaderHandler *>	programs;

    GLuint      texture[1];

    std::vector<GLuint>     vbo; // 0 - particle 1 - gp 2 - font
    std::vector<GLuint>     vao;
};

std::ostream &		operator<<(std::ostream & os, const OGL_manager & gl);

#endif
