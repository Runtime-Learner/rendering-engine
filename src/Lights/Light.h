/**
 * @file Lights.h
 * @author Matthias Arabian
 * @brief Lights interface
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef  __LIGHTS_INTERFACE_RENDERER
#define  __LIGHTS_INTERFACE_RENDERER

#include <vector>
#include <memory>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../BxDFs/sampler.h"

using Eigen::MatrixXd;
using Eigen::RowVector3d;

class Light {
    public:
        struct Interface {
            virtual MatrixXd sampleArea(Sampler sample, RowVector3d hit) = 0;
            virtual double pdfArea() = 0;
            virtual MatrixXd SampleSolidAngle(Sampler sample, RowVector3d hit) = 0;
            virtual double pdfSolidAngle(RowVector3d hit) = 0;
            virtual RowVector3d getRadiance(RowVector3d hit) = 0;
 
            Interface()  {}
            virtual ~Interface() = default;
        };

        std::shared_ptr<Interface> _p;
        Light() {_p = nullptr;}
        Light(Interface* p) : _p(p) {}
};
#endif