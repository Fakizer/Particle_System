#include "Shader.hpp"

Shader::Shader() {}

Shader::Shader(GLenum type, const std::string & path) : type(type), path(path) {
    parse();
    compile();
}

void	Shader::parse()
{
	shader_id = glCreateShader(type);

    std::ifstream VertexShaderStream(path.c_str(), std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        shader_code = sstr.str();
        VertexShaderStream.close();
    }
}

void    Shader::compile() const {
    GLint Result = GL_FALSE;
    int InfoLogLength;

    printf("Компиляция шейдера: %s\n", path.c_str());
    char const * VertexSourcePointer = shader_code.c_str();
    glShaderSource(shader_id, 1, &VertexSourcePointer , NULL);
    glCompileShader(shader_id);

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> ShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(shader_id, InfoLogLength, NULL, &ShaderErrorMessage[0]);
      fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
    }
}

Shader::~Shader() {
    if (shader_id != 0)
		glDeleteShader(shader_id);
}
