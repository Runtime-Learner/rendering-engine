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

#ifndef _RENDERER_MAT__H
#define _RENDERER_MAT__H

#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../Scenes/scene.cpp"
#include "../Shapes/Shapes.h"

using Eigen::RowVector3d;
using Eigen::MatrixXd;
using Eigen::all;
using Eigen::MatrixXi;

class Backward_Raytracing_Matrix {
    public:
        Backward_Raytracing_Matrix() {

        }
        MatrixXd render(Scene scene, int spp, int startx, int endx, int starty, int endy);
};
#endif