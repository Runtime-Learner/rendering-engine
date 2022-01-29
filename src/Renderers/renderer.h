/**
 * @file renderer.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#ifndef _RENDERER_H
#define _RENDERER_H

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include <cmath>
#endif

#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../Scenes/scene.cpp"
#include "../Shapes/Shapes.h"

using Eigen::RowVector3d;
using Eigen::MatrixXd;
using Eigen::all;

class Backward_Raytracing {
    public:
        Backward_Raytracing() {

        }
        MatrixXd render(Scene scene, int spp, int startx, int endx, int starty, int endy);
        static RowVector3d shade(Scene scene, RowVector3d hitPt, RowVector3d wrWorld, int hitShapeID);
};
#endif