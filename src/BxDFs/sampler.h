/**
 * @file sampler.h
 * @author sampler class
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __SAMPLER_LIB
#define __SAMPLER_LIB

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include <corecrt_math_defines.h>
#endif

#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

using Eigen::RowVector3d;
using Eigen::RowVector2d;


class Sampler {
    public:

    Sampler() {
        srand((unsigned int) std::chrono::system_clock::now().time_since_epoch().count());
    }

    double nextSample() {
        double r = ((double) rand() / (RAND_MAX));
        
        return r;
    }

    RowVector2d next2D() {
        return RowVector2d(nextSample(), nextSample());
    }

    static RowVector2d concentricSampleDisk(RowVector2d sample) {
        RowVector2d sampleOffset = 2 * sample - RowVector2d({1, 1});
        double r, theta;
        if (sample.maxCoeff() == 0)
            return RowVector2d({0, 0});
        if (abs(sampleOffset[0]) > abs(sampleOffset[1])) {
            r = sampleOffset[0];
            theta = M_PI_4 * (sampleOffset[1] / sampleOffset[0]);
        }
        else {
            r = sampleOffset[1];
            theta = M_PI_2 - M_PI_4 * (sampleOffset[0] / sampleOffset[1]);  
        }

        return r * RowVector2d({cos(theta), sin(theta)});
    }

    static RowVector3d cosineSampleHemisphere(RowVector2d sample) {
        RowVector2d d = concentricSampleDisk(sample);
        double z = sqrt(std::max(0.0, 1 - d[0] * d[0] - d[1] * d[1]));
        return RowVector3d({d[0], d[1], z});
    }

    static double cosineHemispherePdf(RowVector3d v) {
        return (v[2] > 0) ? v[2] * M_1_PI : 0;
    }
};
#endif