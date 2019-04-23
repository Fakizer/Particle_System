#pragma once

#include "Point.hpp"
// #include <vector>

class GravityManager
{
public:
    unsigned int gpNumb;
    std::vector<Point> points;
    
    GravityManager();
    GravityManager(unsigned int numb);

    Point *     getFreePoint();

    bool		isPointFree(const Point & gp) const;
    void		freePoint(Point & point);
    void		freeAllPoints();

    ~GravityManager();
};
