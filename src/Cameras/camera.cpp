/**
 * @file cameras.h
 * @author Matthias Arabian
 * @brief library file to use in renderer
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CAMERA_RENDERER
#define __CAMERA_RENDERER

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
 
using Eigen::RowVector3d;

class Camera {
    public:
        RowVector3d eye;
        RowVector3d dir;
        RowVector3d up;
        Camera() {
            
        }

        Camera(RowVector3d position, RowVector3d direction, RowVector3d up_direction) {
            eye = position;
            dir = direction;
            up = up_direction;
            up.normalize();
        }
};

#endif