/**
 * @file ray.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 * invdir and sign[3] code comes from:
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
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
        RowVector3d invDir;
        int sign[3];
        double max;

        Ray(RowVector3d origin, RowVector3d direction, double maximum=1e20) {
        o = origin;
        d = direction;
        d.normalize();
        max = maximum;

        invDir = d; //TODO: invDir should be the inverse of d 
        sign[0] = (invDir[0] < 0.0); 
        sign[1] = (invDir[1] < 0.0); 
        sign[2] = (invDir[2] < 0.0); 
        }
};
#endif