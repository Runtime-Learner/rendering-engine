/**
 * @file box.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
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