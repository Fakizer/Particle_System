#include "ShaderHandler.hpp"

ShaderHandler::ShaderHandler() {}

ShaderHandler::ShaderHandler(const std::vector<Shader *> & shaders) {
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Создаем шейдерную программу и привязываем шейдеры к ней
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к ней\n");

    program_id = glCreateProgram();
    for (const Shader * shader : shaders)
        glAttachShader(program_id, shader->shader_id);
    glLinkProgram(program_id);
    // glValidateProgram(program_id);
    for (const Shader * shader : shaders)
		glDetachShader(program_id, shader->shader_id);

    // Проверяем шейдерную программу
    glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      std::vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    // glDeleteShader(shaders[0]->shader_id);
    // glDeleteShader(shaders[1]->shader_id);
}

ShaderHandler::~ShaderHandler() {
    freeGLprog();

	if (program_id != 0)
		glDeleteProgram(program_id);
}

void	ShaderHandler::freeGLprog() const {
	glUseProgram(0);
}

void    ShaderHandler::prog_enable() const {
    glUseProgram(program_id);
}

void	ShaderHandler::prog_disable() const {
	glUseProgram(0);
}

