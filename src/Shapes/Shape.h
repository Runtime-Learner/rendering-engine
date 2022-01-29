/**
 * @file Shape.h
 * @author Matthias Arabian
 * @brief Shapes interface declaration
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 * 
 * 
 * shared_ptr implementation comes from https://stackoverflow.com/a/59015799
 * 
 */

#ifndef __SHAPES_INTERFACE_RENDERER
#define  __SHAPES_INTERFACE_RENDERER
#include <iostream>
#include <vector>
#include <memory>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../BxDFs/BxDFs.h"

using Eigen::RowVector3d;
using Eigen::MatrixXd;
using std::vector;

class Shape {
    public:
        struct Interface {
            bool isLightSource;
            RowVector3d radiance;
            BxDF mat;
            
            virtual RowVector3d normal(RowVector3d point) = 0;
            virtual double intersect(Ray ray)             = 0;
            virtual MatrixXd intersect_matrix(MatrixXd rayDir_mat, RowVector3d initialPt) {
                // std::cout << "Using default intersect_matrix code: " << rayDir_mat.rows() << std::endl;
                MatrixXd result(rayDir_mat.rows(), 1);

                for (int rayId = 0; rayId < rayDir_mat.rows(); rayId++) {
                    
                    Ray r = Ray(initialPt, rayDir_mat.row(rayId));
                    result(rayId) = intersect(r);
                    // std::cout << "RayID: " << rayId << ", val: " << result(rayId) << std::endl;
                }
                return result;
            }

            Frame getFrame(RowVector3d hitPt) {
                return Frame(normal(hitPt));
            }

            // TODO: add support for SIMD matrix_intersect function
            // TODO: FIX: BxDF not properly implemented
            Interface() { isLightSource = false; }
            Interface(RowVector3d rad) { radiance = rad; isLightSource = radiance.maxCoeff() > 0; }
            virtual ~Interface() = default;
        };

        std::shared_ptr<Interface> _p;

        Shape(Interface* p) : _p(p) {
            _p->isLightSource = false;
        }
};

#endif