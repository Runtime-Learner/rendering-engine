/**
 * @file box.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * intersection code comes from:
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
 */

#ifndef __BOX_RENDERER
#define __BOX_RENDERER

#include <iostream> //TODO: delete
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Shape.h"
#include "../BxDFs/BxDFs.h"

using Eigen::RowVector3d;

class Box : public Shape::Interface {
    public:
        RowVector3d vMin;
        RowVector3d vMax;
        BxDF mat;

        Box(RowVector3d v1, RowVector3d v2);
        Box(RowVector3d v1, RowVector3d v2, BxDF bxdf);
        
        RowVector3d normal(RowVector3d point);
        double intersect(Ray r);
};
#endif