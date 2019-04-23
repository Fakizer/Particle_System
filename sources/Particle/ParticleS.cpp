#include "ParticleS.hpp"


ParticleS &	        ParticleS::instance(OGL_manager * glman_in, OCL_manager * clman_in, GravityManager * gm_in)
{
	static ParticleS *	ps;

	if (ps == nullptr)
	{
		if (glman_in != nullptr && clman_in != nullptr)
			ps = new ParticleS(*glman_in, *clman_in, *gm_in);
		else
			printf("The first call to ParticleSystem::instance must have a GL context and a CL context.");
	}

	return *ps;
}

ParticleS::ParticleS(OGL_manager & glman_in, OCL_manager & clman_in, GravityManager & gm_in) : 
    glman(glman_in), 
    clman(clman_in), 
    gm(gm_in), 
    camera(glman_in.window), 
    entries_count(1000000) {
    
    setCLbuffers();

    create_camera();
    init();

    glman.rend_func = [&](void *data){ render(); };
}

void        ParticleS::render() {
    changePS();
    camera.apply_changes_camera();
    updateUniforms();
    Updater::update(*this);
}


void        ParticleS::changePS() {
    static std::clock_t	lastTime = std::clock();
	std::clock_t		newTime;
	cl_float			deltaTime;

	try
	{
		cl::CommandQueue &	queue = clman.queue;

		updateGPBuffer();

		newTime = std::clock();
		deltaTime = 1000.f * (newTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = newTime;

		if (!_paused)
		{
			cl::Kernel	kernel(clman.program, "update_particles");
			kernel.setArg(0, clman.vbos[0]);
			kernel.setArg(1, clman.vbos[1]);
			kernel.setArg(2, sizeof(cl_float), &deltaTime);

			glFinish();

			queue.enqueueAcquireGLObjects(&clman.vbos);
			queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(entries_count), cl::NullRange);
			queue.finish();
			queue.enqueueReleaseGLObjects(&clman.vbos);
		}
	}
	catch (const cl::Error & e)
	{
		printf("An error occured while particles updating %s\n", e.what());
	}
}

void		ParticleS::updateGPBuffer() const {
	glBindBuffer(GL_ARRAY_BUFFER, glman.vbo[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Point) * gm.gpNumb, gm.points.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		ParticleS::updateUniforms() const
{
	const ShaderHandler *	program;
	const Point &	        gp = gm.points[0];
	GLint					uniID;
	const glm::mat4			mvp = camera.projection_mat * glm::inverse(camera.view_mat);


	program = glman.programs.at("particle");
	program->prog_enable();
	uniID = glGetUniformLocation(program->program_id, "gp");
    printf("-------------\n");
	// glUniform4f(uniID, gp.s[0], gp.s[1], gp.s[2], gp.s[3]);
	glUniform4f(uniID, 4, gp);
	uniID = glGetUniformLocation(program->program_id, "mvp");
	glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(mvp));
	program->prog_disable();

    printf("-------------\n");
	program = glman.programs.at("gp");
	program->prog_enable();
	uniID = glGetUniformLocation(program->program_id, "mvp");
	glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(mvp));
	program->prog_disable();
}

void		ParticleS::init()
{
    std::string initFunction("initialize_cube");

	gm.freeAllPoints();

	try
	{
		cl::CommandQueue &	queue = clman.queue;
		cl::Kernel			kernel(clman.program, initFunction.c_str());

		kernel.setArg(0, clman.vbos[0]);
		kernel.setArg(1, sizeof(cl_uint), &entries_count);
		queue.enqueueAcquireGLObjects(&clman.vbos);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(entries_count), cl::NullRange);
		queue.finish();
		queue.enqueueReleaseGLObjects(&clman.vbos);
	}
	catch (const cl::Error & e)
	{
		printf(
			"Error while initializing particles: %s (%i).\n",
			e.what(), e.err());
	}
}

void        ParticleS::setCLbuffers() {
    setupPartBuffer();
	setupGPBuffer();

	try
	{
		cl::BufferGL	clBuffer;

		clman.vbos.push_back(cl::BufferGL(clman.context, CL_MEM_READ_WRITE, glman.vbo[0], nullptr));
		clman.vbos.push_back(cl::BufferGL(clman.context, CL_MEM_READ_ONLY, glman.vbo[1], nullptr));
	}
	catch (const cl::Error & e)
	{
		printf("Error while creating the particle CL buffer");
	}
}

void		ParticleS::setupPartBuffer()
{
	GLuint	size = sizeof(Particle) * static_cast<GLuint>(entries_count);
	GLuint	vbo = glman.vbo[0];
	GLuint	vao = glman.vao[0];
	GLuint	programID = glman.programs["particle"]->program_id;
	GLuint	attribID;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);

	attribID = glGetAttribLocation(programID, "inPosition");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr);

	attribID = glGetAttribLocation(programID, "inVelocity");
	glEnableVertexAttribArray(attribID);
	glVertexAttribPointer(attribID, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *)(sizeof(cl_float4)));

	glBindVertexArray(0);
}

void		ParticleS::setupGPBuffer()
{
	GLuint	size = sizeof(Point) * gm.gpNumb;
	GLuint	vbo = glman.vbo[1];
	GLuint	vao = glman.vao[1];

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, gm.points.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Point), nullptr);

	glBindVertexArray(0);
}

void		ParticleS::create_camera() {
    camera.view_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1.735f));
	camera.linearVelocity = glm::vec3(0.0f);
	camera.angularVelocity = glm::vec3(0.0f);
	camera.quaternion = glm::quat(1, 1, 1, 1);
	camera.aspectratio = glman.window.current_win_w / glman.window.current_win_h;
}

ParticleS::~ParticleS() {
	delete glman.programs["particle"];
	delete glman.programs["gp"];
}
