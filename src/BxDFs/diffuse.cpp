/**
 * @file diffuse.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

using Eigen::RowVector3d;

class Diffuse {
    public:
        RowVector3d c;

        Diffuse() {
            c = RowVector3d(1,1,1);
        }

        Diffuse(RowVector3d color) {
            c = color;
        }
};