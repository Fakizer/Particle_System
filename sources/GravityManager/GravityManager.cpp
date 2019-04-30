// #define __gl3_h_
#include "ParticleS.hpp"
#include "GravityManager.hpp"

// #include <vector>

GravityManager::GravityManager() {}

GravityManager::GravityManager(unsigned int numb) : gpNumb(numb) {
    points.resize(gpNumb);
    memset(points.data(), 0, sizeof(Point) * gpNumb);
}

Point *		GravityManager::getDefaultPoint() {
	Point * point = getFreePoint();
	if (point != nullptr) {
		point->s[0] = 0.0f;
		point->s[1] = 0.0f;
		point->s[2] = 0.0f;
		point->s[3] = 1.0f;
	}
	printf("------------------------\n");
	return point;
}

Point *		GravityManager::getPointInPosFM(glm::vec2 screenPoint) {
	Point * point = getFreePoint();
	printf("%f, %f\n\n", screenPoint.x, screenPoint.y);
	if (point != nullptr) {
		Camera & camera = ParticleS::instance().camera;

		std::vector<glm::vec3> ray = camera.getRay2Point(screenPoint);
		printf("%f, %f, %f\n", ray[0].x, ray[0].y, ray[0].z);
		printf("%f, %f, %f\n", ray[1].x, ray[1].y, ray[1].z);
		float distance_to_plane = glm::length(glm::vec3(0) - glm::vec3(0,0,2));
		glm::vec3 planePosition = camera.cf * distance_to_plane + camera.camPos;
		glm::vec3 planeNormal = glm::normalize(camera.camPos - planePosition);

		float	distance = -1.f * glm::dot((ray[0] - planePosition), planeNormal) / glm::dot(ray[1], planeNormal);

		glm::vec3 position = ray[0] + (ray[1] * distance);

		printf("%f, %f, %f\n", position.x, position.y, position.z);
		point->s[0] = position.x;
		point->s[1] = position.y;
		point->s[2] = position.z;
		point->s[3] = 1.0f;
	}
	printf("------------------------\n");
	return point;
}

Point *		GravityManager::getPointInPos(glm::vec2 screenPoint) {
	Point * point = getFreePoint();
	printf("%f, %f\n\n", screenPoint.x, screenPoint.y);
	if (point != nullptr) {
		Camera & camera = ParticleS::instance().camera;

		std::vector<glm::vec3> ray = camera.getRay2Point(screenPoint);
		printf("%f, %f, %f\n", ray[0].x, ray[0].y, ray[0].z);
		printf("%f, %f, %f\n", ray[1].x, ray[1].y, ray[1].z);
		float distance_to_plane = glm::length(glm::vec3(0) - glm::vec3(0,0,2));
		glm::vec3 planePosition = camera.cf * distance_to_plane + camera.camPos;
		glm::vec3 planeNormal = glm::normalize(camera.camPos - planePosition);

		float	distance = -1.f * glm::dot((ray[0] - planePosition), planeNormal) / glm::dot(ray[1], planeNormal);

		glm::vec3 position = ray[0] + (ray[1] * distance);

		printf("%f, %f, %f\n", position.x, position.y, position.z);
		point->s[0] = position.x;
		point->s[1] = position.y;
		point->s[2] = position.z;
		point->s[3] = 1.0f;
	}
	printf("------------------------\n");
	return point;
}

Point *	        GravityManager::getFreePoint()
{
	for (Point & point : points)
	{
		if (!isPointFree(point))
			return &point;
	}

	return nullptr;
}

bool			GravityManager::isPointFree(const Point & point) const
{
	return (point.s[3] != 0);
}

void			GravityManager::freePoint(Point & point)
{
	point.s[3] = 0;
}

void			GravityManager::freeAllPoints()
{
	for (Point & point : points)
		freePoint(point);
}


GravityManager::~GravityManager() {}
