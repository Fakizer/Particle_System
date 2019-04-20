#ifndef SHADER_HPP
#define SHADER_HPP

#define __gl3_h_

#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Shader {
public:
    Shader();
    Shader(GLenum type, const std::string & path);
    ~Shader();

    void	parse();
    void    compile();

    GLenum          type;
    std::string     path;
    GLuint          shader_id;
    std::string     shader_code;


    GLuint			part_vbos;
    GLuint			part_vaos;
    GLuint			gp_vbos;
    GLuint			gp_vaos;
};

#endif
