#pragma once

#include "Point.hpp"

#include "Camera.hpp"

class GravityManager
{
public:
    unsigned int gpNumb;
    std::vector<Point> points;
    
    GravityManager();
    GravityManager(unsigned int numb);

    Point *     getDefaultPoint();
    Point *     getPointInPos(glm::vec2 screenPoint);
    Point *     getPointInPosFM(glm::vec2 screenPoint);
    Point *     getFreePoint();

    bool		isPointFree(const Point & gp) const;
    void		freePoint(Point & point);
    void		freeAllPoints();

    ~GravityManager();
};
