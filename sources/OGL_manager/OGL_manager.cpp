#include "OGL_manager.hpp"

OGL_manager::OGL_manager() : window() {
    if (!initGLFW())
        exit(0);

    if (!initWindow())
        exit(0);

    if (!initGlew())
        exit(0);

    glfwSetKeyCallback(window.win, keyboard.key_callback);
    glfwSetMouseButtonCallback(window.win, mouse.mouse_click_callback);
	glfwSetCursorPosCallback(window.win, mouse.mouse_move_callback);
	// glfwSetWindowSizeCallback(window.win, GLContext::resizeWindow);
    createPrograms();
    createVO();
}

bool    OGL_manager::initGLFW() {
    if (!glfwInit()) {
		throw PS_errors::GLFW_init();
        return false;
    }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    return true;
}

bool    OGL_manager::initWindow() {
    window.win = glfwCreateWindow(window.current_win_w, window.current_win_h, "Partical System", nullptr, nullptr);

    if (window.win == NULL) {
        throw PS_errors::Win_init();
        return false;
    }
    glfwMakeContextCurrent(window.win);
    return true;
}

bool    OGL_manager::initGlew() {
    if (glewInit() != GLEW_OK) {
		throw PS_errors::Glew_init();
        return false;
    }
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1.f);
    return true;
}

void    OGL_manager::createPrograms() {

    Shader p_v(GL_VERTEX_SHADER, "shader/particle_vertex.glsl");
    Shader p_f(GL_FRAGMENT_SHADER, "shader/particle_fragment.glsl");
    programs["particle"] = new ShaderHandler({&p_v, &p_f});

    Shader gp_v(GL_VERTEX_SHADER, "shader/gp_vertex.glsl");
    Shader gp_f(GL_FRAGMENT_SHADER, "shader/gp_fragment.glsl");
    programs["gp"] = new ShaderHandler({&gp_v, &gp_f});

    Shader font_v(GL_VERTEX_SHADER, "shader/font_vertex.glsl");
    Shader font_f(GL_FRAGMENT_SHADER, "shader/font_fragment.glsl");
    programs["font"] = new ShaderHandler({&font_v, &font_f});
}

void    OGL_manager::createVO() {
    GLuint	vbos[3];
	GLuint	vaos[3];

	glGenBuffers(3, vbos);
	vbo.push_back(vbos[0]);
    vbo.push_back(vbos[1]);
    vbo.push_back(vbos[2]);

	glGenVertexArrays(3, vaos);
	vao.push_back(vaos[0]);
    vao.push_back(vaos[1]);
    vao.push_back(vaos[2]);

    glGenTextures(1, texture);
}

void    OGL_manager::rend_img_win(void * prog) {
    while (!glfwWindowShouldClose(window.win))
	{
        
        if (prog != nullptr)
            rend_func(prog);
		// glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window.win);
		glfwPollEvents();
	}  
}


OGL_manager::~OGL_manager() {
	glfwTerminate();
}

std::ostream &		operator<<(std::ostream & os, const OGL_manager & gl)
{
	os << glGetString(GL_VERSION);

	return os;
}
