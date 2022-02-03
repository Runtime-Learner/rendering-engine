/**
 * @file sampler.h
 * @author Matthias Arabian
 * @brief The sampler class contains all standalone sampling methods, and includes methods to generate NxM matrices of random numbers.
 * @version 0.2
 * @date 2022-01-28
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
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

    /**
     * @brief Construct a new Sampler object
     * 
     */
    Sampler() {
        srand((unsigned int) std::chrono::system_clock::now().time_since_epoch().count());
    }

    /**
     * @brief Return a random number in range [0, 1)
     * 
     * @return double random number in range [0, 1)
     */
    double nextSample() {
        #ifdef _MSC_VER
            double r = ( rand() / ((double)(RAND_MAX + 1)));
        #else
            double r = ( rand() / ((double)(RAND_MAX)));
        #endif
        
        
        return r;
    }

    /**
     * @brief Returns a 2D vector where all elements are random numbers in range [0, 1)
     * 
     * @return RowVector2d 2D vector where all elements are random numbers in range [0, 1)
     */
    RowVector2d next2D() {
        return RowVector2d(nextSample(), nextSample());
    }

    /**
     * @brief Returns a NxM matrix where all elements are random numbers in range [0, 1)
     * 
     * @param row N dimension of matrix
     * @param col M dimension of matrix
     * @return MatrixXd NxM matrix where all elements are random numbers in range [0, 1)
     */
    MatrixXd nextMatrix(int row, int col) {
        return (MatrixXd::Random(row, col).array() + 1.0) / 2.0;
    }
    
    /**
     * @brief sample a concentric disk. See 
     * 
     * @param sample 2D random sample
     * @return RowVector2d sampled point on disk
     * @see https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#SamplingaUnitDisk
     */
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

    /**
     * @brief uniformly sample a triangle
     * 
     * @param sample 2D random sample
     * @return RowVector2d sampled point on triangle
     * @see https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#SamplingaTriangle
     */
    static RowVector2d uniformSampleTriangle(RowVector2d sample) {
        double u = sqrt(1 - sample[0]);
        return RowVector2d(1 - u, u * sample[1]);
    }

    /**
     * @brief sample a point from a hemisphere by using cosine hemisphere biasing
     * 
     * @param sample 2D random sample
     * @return RowVector3d sampled point on hemisphere (local frame)
     * @see https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#Cosine-WeightedHemisphereSampling
     */
    static RowVector3d cosineSampleHemisphere(RowVector2d sample) {
        RowVector2d d = concentricSampleDisk(sample);
        double z = sqrt(std::max(0.0, 1 - d[0] * d[0] - d[1] * d[1]));
        return RowVector3d({d[0], d[1], z});
    }

    /**
     * @brief return probability of sampling a certain point using the cosineSampleHemisphere sampling function
     * 
     * @param v sampled point
     * @return double probability of having sampled that point using the cosineSampleHemisphere sampling function
     * @see https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#Cosine-WeightedHemisphereSampling
     */
    static double cosineHemispherePdf(RowVector3d v) {
        return (v[2] > 0) ? v[2] * M_1_PI : 0;
    }


    //TODO: find source for samplePhongLobe code
    /**
     * @brief uniformly sample a phong lobe
     * 
     * @param sample 2D random sample
     * @param n shininess index of lobe
     * @return RowVector3d sampled point on lobe (in lobe's local frame)
     */
    static RowVector3d uniformSamplePhongLobe(RowVector2d sample, int n) {
        double z = pow(1 - sample[0], 1 / (n + 1));
        double r = sqrt(1 - z * z);
        double phi = 2 * M_PI * sample[1];
        double x = r * cos(phi);
        double y = r * sin(phi);
        return RowVector3d({x, y, z});
    }
    
    /**
     * @brief return probability of having sampled wi using the uniformSamplePhongLobe sampling function
     * 
     * @param wi sampled point
     * @param n shininess index of lobe
     * @return double probability of having sampled wi using the uniformSamplePhongLobe sampling function
     */
    static double uniformPhongLobePdf(RowVector3d wi, int n) {
        return (n + 1) / (2 * M_PI) * pow(wi[2], n);
    }
};
#endif