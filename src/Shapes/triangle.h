/**
 * @file triangle.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TRIANGLE_RENDERER
#define __TRIANGLE_RENDERER
#include <iostream> //TODO: delete
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Shape.h"

using Eigen::RowVector3d;

class Triangle : public Shape::Interface {
    public:
        RowVector3d v0;
        RowVector3d v1;
        RowVector3d v2;

        Triangle(RowVector3d a, RowVector3d b, RowVector3d c);
        Triangle(RowVector3d a, RowVector3d b, RowVector3d c, RowVector3d color);
        
        RowVector3d normal(RowVector3d point);
        RowVector3d normal();
        double intersect(Ray r);
};
#endif