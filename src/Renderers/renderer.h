/**
 * @file renderer.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _RENDERER_CPP
#define _RENDERER_CPP

#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../Scenes/scene.cpp"

using Eigen::RowVector3d;
using Eigen::MatrixXd;
using Eigen::all;

class Backward_Raytracing {
    public:
        Backward_Raytracing() {

        }
        MatrixXd render(Scene scene);

};
#endif