#include "OGL_manager.hpp"
#include <vector>

OGL_manager::OGL_manager() : window(), keyboard(window) {
    if (!initGLFW())
        exit(0);

    if (!initWindow())
        exit(0);

    if (!initGlew())
        exit(0);

    glfwSetKeyCallback(window.win, keyboard.key_callback);
    createPrograms();
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
    window.win = glfwCreateWindow(window.current_win_w, window.current_win_h, "Hello World", nullptr, nullptr);

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

    std::vector<int> zzz {1, 2, 3, 4};
    std::vector<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};

    programs["particle"] = new ShaderHandler({
        &Shader(GL_VERTEX_SHADER, "shader/particle_vertex.glsl"),
        &Shader(GL_FRAGMENT_SHADER, "shader/particle_fragment.glsl")
    });

    programs["gp"] = new ShaderHandler({
        &Shader(GL_VERTEX_SHADER, "shader/gp_vertex.glsl"),
        &Shader(GL_FRAGMENT_SHADER, "shader/gp_fragment.glsl")
    });
}

void    OGL_manager::rend_img_win() {
    std::cout << (window.win == NULL) << std::endl;
    while (!glfwWindowShouldClose(window.win))
	{
		glfwPollEvents();
		glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window.win);
	}  
}

OGL_manager::~OGL_manager() {
	glfwTerminate();
}
