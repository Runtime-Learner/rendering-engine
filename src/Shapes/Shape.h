/**
 * @file Shape.h
 * @author Matthias Arabian
 * @brief Shapes interface declaration
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * shared_ptr implementation comes from https://stackoverflow.com/a/59015799
 * 
 */

#ifndef __SHAPES_INTERFACE_RENDERER
#define  __SHAPES_INTERFACE_RENDERER

#include <vector>
#include <memory>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../BxDFs/BxDFs.h"

using Eigen::RowVector3d;
using std::vector;

class Shape {
    public:
        struct Interface {
            bool isLightSource;
            RowVector3d radiance;
            BxDF mat;
            virtual RowVector3d normal(RowVector3d point) = 0;
            virtual double intersect(Ray ray)             = 0;

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