/**
 * @file triangle.h
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

#ifndef __TRIANGLE_RENDERER
#define __TRIANGLE_RENDERER
#include <iostream> //TODO: delete
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Shape.h"
#include "../BxDFs/BxDFs.h"

using Eigen::RowVector3d;

class Triangle : public Shape::Interface {
    public:
        RowVector3d v0;
        RowVector3d v1;
        RowVector3d v2;

        Triangle(RowVector3d a, RowVector3d b, RowVector3d c);
        Triangle(RowVector3d a, RowVector3d b, RowVector3d c, BxDF bxdf);
        
        RowVector3d normal(RowVector3d point);
        RowVector3d normal();
        double intersect(Ray r);
        MatrixXd intersect_matrix(MatrixXd rayDir_mat, RowVector3d initialPt);
};
#endif