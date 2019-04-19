#include "ParticleS.hpp"
#include <glew/glew.h>


bool animate = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cerr << "key_callback(" << window << ", " << key << ", " << scancode << ", " << action << ", " << mode << ");" << std::endl;
    if (GLFW_RELEASE == action) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        animate = !animate;
    }
}

int setup_window(GLFWwindow* &window, int width, int height) {
    std::cerr << "Starting GLFW context, OpenGL 4.0" << std::endl;
    if (!glfwInit())
        std::cout << "Failed to init GLFW" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "OpenGL starter pack", NULL, NULL);
    glfwMakeContextCurrent(window);
    // glfwGetFramebufferSize(window, &width, &height);
    std::cout << "-------------" << std::endl;
	// glViewport(0, 0, width, height);
    std::cout << "-------------" << std::endl;
	// glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     std::cerr << "Failed to initialize OpenGL context" << std::endl;
    //     return -1;
    // }

    return 0;
}

void	looper(void)
{
	glfwPollEvents();
	glClearColor(0.09f, 0.08f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(void) {

    GLFWwindow* window = nullptr;
    const int width = 1280, height = 1024;

    if (!glfwInit())
		printf("Count not init glfw.");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Hello World", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		printf("Could not create a window.");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		printf("Count not init glew.");

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1.f);
//     std::cout << "ky" << std::endl;
    
//     cl_platform_id      platform_id;
//     cl_uint             ret_num_platforms;
//     cl_device_id        device_id;
//     cl_uint             ret_num_devices;

//     /* получить доступные платформы */
//     auto ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

// /* получить доступные устройства */
//     ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

// /* создать контекст */
//     auto context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

// /* создаем команду */
//     auto command_queue = clCreateCommandQueue(context, device_id, 0, &ret);


//     cl_program program = NULL;
//     cl_kernel kernel = NULL;

//     FILE *fp;
//     const char fileName[] = "./sources/test_kernel.cl";
//     size_t source_size;
//     char *source_str;
//     int i;

//     try {
//         fp = fopen(fileName, "r");
//         if (!fp) {
//             fprintf(stderr, "Failed to load kernel.\n");
//             exit(1);
//         }
//         source_str = (char *)malloc(MAX_SOURCE_SIZE);
//         source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
//         fclose(fp);
//     } 
//     catch (int a) {
//         printf("%d", a);
//     }

//     /* создать бинарник из кода программы */
//     program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

//     /* скомпилировать программу */
//     ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

//     /* создать кернел */
//     kernel = clCreateKernel(program, "test", &ret);

//     cl_mem memobj = NULL;
//     int memLenth = 10;
//     cl_int* mem = (cl_int *)malloc(sizeof(cl_int) * memLenth);

//     /* создать буфер */
//     memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, memLenth * sizeof(cl_int), NULL, &ret);

//     /* записать данные в буфер */
//     ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(cl_int), mem, 0, NULL, NULL);

//     /* устанавливаем параметр */
//     ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

//     size_t global_work_size[1] = { 10 };

//     /* выполнить кернел */
//     ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);

//     /* считать данные из буфера */
//     ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(float), mem, 0, NULL, NULL);

// ///////////////////////////////////////////////////////

//     const int width = 1280, height = 1024;
//     setup_window(window, width, height);
//     while (!glfwWindowShouldClose(window))
// 	{
// 		looper();
//         glfwSwapBuffers(window);
// 	}
    return (0);
}
