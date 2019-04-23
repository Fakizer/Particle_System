
#define __gl3_h_

#include <iostream>
// #include <glad/glad.h>
#include <glew/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Updater.hpp"
#include "ParticleS.hpp"
#include "FPS_manager.hpp"

void		Updater::update(const ParticleS & ps)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Updater::updateParticles(ps);
	Updater::updatePoints(ps);
	Updater::updateWindowTitle(ps);

	FPS_manager::update();
}

void		Updater::updateParticles(const ParticleS & ps)
{
	OGL_manager &		glman = ps.glman;
	ShaderHandler *	program = glman.programs["particle"];

	glBindVertexArray(glman.vao[0]);
	program->prog_enable();
	glDrawArrays(GL_POINTS, 0, ps.entries_count);
	program->prog_disable();
	glBindVertexArray(0);
}

void		Updater::updatePoints(const ParticleS & ps)
{
	OGL_manager &		glman = ps.glman;
	ShaderHandler *	program = glman.programs["gp"];

	glBindVertexArray(glman.vao[1]);
	program->prog_enable();
	glDrawArrays(GL_POINTS, 0, ps.gm.gpNumb);
	program->prog_disable();
	glBindVertexArray(0);
}

void		Updater::updateWindowTitle(const ParticleS & ps)
{
	char	title[50];
	float	fps = FPS_manager::fps;

	if (fps < 0)
		return;

	sprintf(title, "%i fps", static_cast<int>(fps));
	glfwSetWindowTitle(ps.glman.getWindow().win, title);
}