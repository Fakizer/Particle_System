#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(Window & win) :
    resolution(win.current_win_w, win.current_win_h),
    view_mat(glm::mat4(1.0f)),
    initialFoV(45.0f),
    nearPlane(0.001f),
    farPlane(100.0f) {

    initCamera();
    aspectratio = resolution.x / resolution.y ;
}

void                    Camera::initCamera() {

    camPos = glm::vec3(0, 0, 2);

    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
	aspectratio = resolution.x / resolution.y;

    speed = 3.0f; // 3 units / second
    
    // arrows_speed = 0.005f;
    arrows_speed = 0.01f;


    cf = camDir = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    cr = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    cu = glm::cross( cr, cf );

    projection_mat = glm::perspective(
        glm::radians(initialFoV), 
        aspectratio, nearPlane, farPlane
    );

    view_mat = glm::lookAt(
        camPos,           // Позиция камеры
        camPos + camDir, // Направление камеры
        cu                  // Вектор "Вверх" камеры
    );
    
	// linearVelocity = glm::vec3(0.0f);
	// angularVelocity = glm::vec3(0.0f);
	// quaternion = glm::quat(1, 1, 1, 1);
}

std::vector<glm::vec3>      Camera::getRay2Point(glm::vec2 point) {
    printf("-----------------------------start\n");
    glm::vec2 xyamnt = xyamount((int)point.x, (int)point.y);

    glm::vec2	renderPlaneSize;
    
	// renderPlaneSize.y = tan(initialFoV / 2.f) * nearPlane;
	// renderPlaneSize.x = renderPlaneSize.y * aspectratio;

    curRayDir = -cf + (cu * (xyamnt.x - 0.5f)) + (-cr * (xyamnt.y - 0.5f));

	curRayDir = glm::normalize(curRayDir);

	std::vector<glm::vec3>		ray( { camPos, curRayDir } );
    printf("-----------------------------end\n");
	return ray;
}

glm::vec2              Camera::xyamount(int x, int y) {
    width = resolution.x;
    height = resolution.y;
    if (width > height) {
        xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
        yamnt = ((height - y) + 0.5)/height;
    }
    else if (height > width) {
        xamnt = (x + 0.5)/ width;
        yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
    }
    else {
        xamnt = (x + 0.5)/width;
        yamnt = ((height - y) + 0.5)/height;
    }
    glm::vec2 vect = glm::vec2(xamnt, yamnt);
    return vect;
}


void    Camera::apply_changes_camera() {
    moveCamera_QWEASD();
    moveCamera_ARROWS();

    cf = camDir = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    cr = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    cu = glm::cross( cr, cf );
    
    projection_mat = glm::perspective(
        glm::radians(initialFoV), 
        aspectratio, nearPlane, farPlane
    );

    view_mat = glm::lookAt(
        camPos,           // Позиция камеры
        camPos + cf, // Направление камеры
        cu                  // Вектор "Вверх" камеры
    );

}

void    Camera::moveCamera_QWEASD() {
    // static std::clock_t	lastTime = std::clock();
	// std::clock_t		newTime;
	// cl_float			deltaTime;
    glm::vec3           direction(0.0f);

    if (Keyboard::repeater_qweasd["forward"] == true) {
        direction = cf;
        camPos += direction * (speed / FPS_manager::fps);
    }
    if (Keyboard::repeater_qweasd["back"] == true) {
        direction = -cf;
        camPos += direction * (speed / FPS_manager::fps);
    }
    if (Keyboard::repeater_qweasd["right"] == true) {
        direction = cr;
        camPos += direction * (speed / FPS_manager::fps);
    }
    if (Keyboard::repeater_qweasd["left"] == true) {
        direction = -cr;
        camPos += direction * (speed / FPS_manager::fps);
    }
    if (Keyboard::repeater_qweasd["up"] == true) {
        direction = cu;
        camPos += direction * (speed / FPS_manager::fps);
    }
    if (Keyboard::repeater_qweasd["down"] == true) {
        direction = -cu;
        camPos += direction * (speed / FPS_manager::fps);
    }
    
    // newTime = std::clock();
    // deltaTime = 1000.f * (newTime - lastTime) / CLOCKS_PER_SEC;
    // lastTime = newTime;
    // camPos += direction * speed / FPS_manager::fps;
}

void    Camera::moveCamera_ARROWS() {
    float dir = 0.0f;

    if (Keyboard::repeater_arrows["right"] == true) {
        dir = -1.0f;
        horizontalAngle += arrows_speed  * dir;        
    }
    if (Keyboard::repeater_arrows["left"] == true) {
        dir = 1.0f;
        horizontalAngle += arrows_speed  * dir;        
    }
    if (Keyboard::repeater_arrows["up"] == true) {
        dir = 1.0f;
        verticalAngle   += arrows_speed  * dir;
    }
    if (Keyboard::repeater_arrows["down"] == true) {
        dir = -1.0f;
        verticalAngle   += arrows_speed  * dir; 
    }


    // horizontalAngle += arrows_speed  * dir;
    // verticalAngle   += arrows_speed  * dir;
}

void    Camera::reset() {
    view_mat = glm::mat4(1.0f);
}

Camera::~Camera() {}
