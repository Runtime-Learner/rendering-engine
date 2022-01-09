/**
 * @file diffuse.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "BxDF.h"
#include "Frame.h"

using Eigen::RowVector3d;

class DiffuseBRDF : public BxDF::Interface {
    public:
        RowVector3d albedo;

        DiffuseBRDF() {
            albedo = RowVector3d(1,1,1);
        }

        DiffuseBRDF(RowVector3d color) {
            albedo = color;
        }

        //TODO: implement
        RowVector3d eval(RowVector3d hitPt, RowVector3d wi, RowVector3d wr) {
            Frame frame = Frame({0,0,1});
            return albedo * M_1_PI * frame.cosTheta(wi);
        }
        double sample(Sampler sampler, RowVector3d wr) {
            return 0;
        }
        double pdf(RowVector3d wi, RowVector3d wr) {
            return 0;
        }


};