#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
// #include <glm/glm.hpp>
// #include <glm/gtx/transform.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.hpp"

class Camera
{
private:
    glm::vec2       resolution;
    glm::mat4       matrix;

    int             width, height;
    glm::mat4       model_mat;

	float   		initialFoV;
    float           FoV;
    float           verticalAngle;
    float           horizontalAngle;


	float	    	nearPlane;
	float		    farPlane;
    float           xamnt, yamnt;


    void            initCamera();
    glm::vec2       xyamount(int x, int y);

public:
    float           aspectratio;
    glm::quat       quaternion;
    glm::mat4       projection_mat;
    glm::mat4       view_mat;
    glm::vec3		linearVelocity;
	glm::vec3		angularVelocity;

    float           speed;
    glm::vec3       camPos, camDir, curRayDir;
    glm::vec3       cu, cr, cf;


    Camera();
    Camera(Window & win);

    std::vector<glm::vec3>  getRay2Point(glm::vec2 point);
    void        apply_changes_camera();
    void        apply_changes_projec();
    void        reset();
    ~Camera();
};

#endif
