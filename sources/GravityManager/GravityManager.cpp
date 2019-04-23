#include "GravityManager.hpp"

GravityManager::GravityManager() {}

GravityManager::GravityManager(unsigned int numb) : gpNumb(numb) {
    points.resize(gpNumb);
    memset(points.data(), 0, sizeof(Point) * gpNumb);
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
