/**
 * @file sphere.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __SPHERE_RENDERER
#define __SPHERE_RENDERER

#include <iostream> //TODO: delete
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Shape.h"
#include "../BxDFs/BxDFs.h"

using Eigen::RowVector3d;

class Sphere : public Shape::Interface {
    public:
        RowVector3d c;
        double r;

        Sphere(RowVector3d center, double radius);
        Sphere(RowVector3d center, double radius, BxDF bxdf);
        
        RowVector3d normal(RowVector3d point);
        double intersect(Ray r);
        // MatrixXd intersect_matrix(MatrixXd rayDir_mat, RowVector3d initialPt);
};
#endif