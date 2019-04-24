// #define __gl3_h_
#include "ParticleS.hpp"
#include "GravityManager.hpp"

// #include <vector>

GravityManager::GravityManager() {}

GravityManager::GravityManager(unsigned int numb) : gpNumb(numb) {
    points.resize(gpNumb);
    memset(points.data(), 0, sizeof(Point) * gpNumb);
}

Point *		GravityManager::getDefaultPoint(glm::vec2 screenPoint) {
	Point * point = getFreePoint();

	if (point != nullptr) {
		Camera & camera = ParticleS::instance().camera;

		std::vector<glm::vec3> ray = camera.getRay2Point(screenPoint);

		glm::vec3 planeNormal = camera.quaternion * glm::vec3(0,0,-1.0f);
		glm::vec3 planePosition(0);

		float	distance = glm::dot(planeNormal, (planePosition - ray[0])) / glm::dot(planeNormal, ray[1]);

		glm::vec3 position = ray[0] + ray[1] * distance;

		point->s[0] = position.x;
		point->s[1] = position.y;
		point->s[2] = position.z;
		point->s[3] = 1.0f;
	}
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
