/**
 * @file cameras.h
 * @author Matthias Arabian
 * @brief main file used to compile the Camera library using CMake
 * @version 0.2
 * @date 2022-01-28
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
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

        //TODO: add default values for eye, dir and up?
        Camera() {
        }

        /**
         * @brief Construct a new Camera object
         * 
         * @param position position of camera
         * @param direction  a point (world coordinate) that the camera is facing
         * @param up_direction up direction of camera
         */
        Camera(RowVector3d position, RowVector3d direction, RowVector3d up_direction) {
            eye = position;
            dir = direction;
            up = up_direction;
            up.normalize();
        }
};

#endif