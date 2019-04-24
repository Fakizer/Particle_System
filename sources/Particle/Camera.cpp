#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(Window & win) :
    resolution(win.current_win_w, win.current_win_h),
    view_mat(glm::mat4(1.0f)),
    fovY(glm::pi<float>() * 0.25f),
    nearPlane(0.001f),
    farPlane(100.0f) {

    
    aspectratio = resolution.x / resolution.y ;
    apply_changes_projec();
}

std::vector<glm::vec3>      Camera::getRay2Point(glm::vec2 point) {
    glm::vec3 camForward = quaternion * glm::vec3(0,0,1.0f);
    glm::vec3 camRight = quaternion * glm::vec3(1.0f,0,0);
    glm::vec3 camUp = quaternion * glm::vec3(0,1.0f,0);
    glm::vec3 camPos = view_mat * glm::vec4(0.0f);
	glm::vec2	renderPlaneSize;
    
	renderPlaneSize.y = tan(fovY / 2.f) * nearPlane;
	renderPlaneSize.x = renderPlaneSize.y * aspectratio;

	camRight *= renderPlaneSize.x;
	camUp *= renderPlaneSize.y;
	glm::vec2	viewportPosition = (point - resolution / 2.f) / (resolution / 2.f);
	viewportPosition.y *= -1.f;
	glm::vec3	rayOnNearPlane = camPos + camForward * nearPlane + camRight * viewportPosition.x + camUp * viewportPosition.y;


	glm::vec3 camDir = rayOnNearPlane - camPos;
	camDir = glm::normalize(camDir);

	std::vector<glm::vec3>		ray( { camPos, camDir } );

	return ray;
}



void    Camera::apply_changes_camera() {
    quaternion *= glm::quat(angularVelocity);

    view_mat = glm::rotate(view_mat, angularVelocity.z, glm::vec3(0.0f, 0.0f, -1.0f));
	view_mat = glm::rotate(view_mat, angularVelocity.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	view_mat = glm::rotate(view_mat, angularVelocity.x, glm::vec3(0.0f, -1.0f, 0.0f));
	view_mat = glm::translate(view_mat, linearVelocity);
}

void   Camera::apply_changes_projec() {
    projection_mat = glm::perspective(fovY, aspectratio, nearPlane, farPlane);
}

void    Camera::reset() {
    view_mat = glm::mat4(1.0f);
}

Camera::~Camera() {}
