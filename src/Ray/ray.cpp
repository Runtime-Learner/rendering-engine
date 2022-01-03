/**
 * @file ray.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __RAY_RENDERER
#define __RAY_RENDERER

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
 
using Eigen::RowVector3d;

class Ray {
    public:
        RowVector3d o;
        RowVector3d d;
        double max;

        Ray(RowVector3d origin, RowVector3d direction, double maximum=1e20) {
        o = origin;
        d = direction;
        d.normalize();
        max = maximum;
        }
};
#endif