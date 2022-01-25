/**
 * @file quadlight.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __QUADLIGHT_RENDERER
#define __QUADLIGHT_RENDERER

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "Light.h"
 
using Eigen::RowVector3d;
using Eigen::RowVector2d;
using Eigen::MatrixXd;

class QuadLight : public Light::Interface {
    public:
        RowVector3d v0, v1, v2, v3;
        RowVector3d radiance;
        double area1;
        double area;

        QuadLight() {
        }
        
        QuadLight(RowVector3d vertex0, RowVector3d vertex1, RowVector3d vertex2, RowVector3d vertex3, RowVector3d rad) {
            v0 = vertex0;
            v1 = vertex1;
            v2 = vertex2;
            v3 = vertex3;
            radiance = rad;
            double normTriangle1 = ((v1 - v0).cross(v3 - v0)).norm();
            double normTriangle = ((v2 - v0).cross(v3 - v0)).norm();
            area1 = 0.5 * normTriangle1;
            area = area1 + 0.5 * normTriangle;
        }

        MatrixXd sampleArea(Sampler sampler, RowVector3d hit);
        double pdfArea();
        MatrixXd SampleSolidAngle(Sampler sampler, RowVector3d hit);
        double pdfSolidAngle(RowVector3d hit);
        RowVector3d getRadiance(RowVector3d hit);
};
#endif