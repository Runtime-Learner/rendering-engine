/**
 * @file pointlight.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __POINTLIGHT_RENDERER
#define __POINTLIGHT_RENDERER

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Light.h"
 
using Eigen::RowVector3d;
using Eigen::MatrixXd;

class PointLight : public Light::Interface {
    public:
        RowVector3d pos;
        RowVector3d radiance;

        PointLight() {
        }
        
        PointLight(RowVector3d position, RowVector3d rad) {
            pos = position;
            radiance = rad;
        }

        MatrixXd sampleArea(Sampler sampler, RowVector3d hit);
        double pdfArea();
        MatrixXd SampleSolidAngle(Sampler sampler, RowVector3d hit);
        double pdfSolidAngle(RowVector3d hit);
        RowVector3d getRadiance(RowVector3d hit);
};
#endif