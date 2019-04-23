#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(Window & win) : 
    view_mat(glm::mat4(1.0f)),
    fovY(glm::pi<float>() * 0.25f),
    aspectratio(16.0f / 9.0f),
    nearPlane(0.1f),
    farPlane(100.0f) {

    apply_changes_projec();
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
