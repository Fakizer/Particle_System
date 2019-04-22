#ifndef SHADERHANDLER_HPP
#define SHADERHANDLER_HPP

#include "Shader.hpp"

class ShaderHandler {

private:
        
public:
    ShaderHandler();
    ShaderHandler(const std::vector<Shader *> & shaders);
    ~ShaderHandler();

    void	freeGLprog() const;



    GLuint      program_id = 0;
};



#endif
