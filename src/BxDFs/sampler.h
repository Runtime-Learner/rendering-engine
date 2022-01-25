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


#ifdef _MSC_VER
    #ifndef _USE_MATH_DEFINES
        #define _USE_MATH_DEFINES
        #include <corecrt_math_defines.h>
    #endif
#endif


#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

using Eigen::RowVector3d;
using Eigen::RowVector2d;
using Eigen::MatrixXd;


class Sampler {
    public:

    Sampler() {
        srand((unsigned int) std::chrono::system_clock::now().time_since_epoch().count());
    }

    double nextSample() {
        #ifdef _MSC_VER
            double r = ( rand() / ((double)(RAND_MAX + 1)));
        #else
            double r = ( rand() / ((double)(RAND_MAX)));
        #endif
        
        
        return r;
    }

    RowVector2d next2D() {
        return RowVector2d(nextSample(), nextSample());
    }

    MatrixXd nextMatrix(int row, int col) {
        return (MatrixXd::Random(row, col).array() + 1.0) / 2.0;
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

    static RowVector2d uniformSampleTriangle(RowVector2d sample) {
        double u = sqrt(1 - sample[0]);
        return RowVector2d(1 - u, u * sample[1]);
    }

    static RowVector3d cosineSampleHemisphere(RowVector2d sample) {
        RowVector2d d = concentricSampleDisk(sample);
        double z = sqrt(std::max(0.0, 1 - d[0] * d[0] - d[1] * d[1]));
        return RowVector3d({d[0], d[1], z});
    }

    static double cosineHemispherePdf(RowVector3d v) {
        return (v[2] > 0) ? v[2] * M_1_PI : 0;
    }

    static RowVector3d uniformSamplePhongLobe(RowVector2d sample, int n) {
        double z = pow(1 - sample[0], 1 / (n + 1));
        double r = sqrt(1 - z * z);
        double phi = 2 * M_PI * sample[1];
        double x = r * cos(phi);
        double y = r * sin(phi);
        return RowVector3d({x, y, z});
    }
    
    static double uniformPhongLobePdf(RowVector3d wi, int n) {
        return (n + 1) / (2 * M_PI) * pow(wi[2], n);
    }
};
#endif