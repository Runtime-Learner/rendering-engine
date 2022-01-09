/**
 * @file pointlight.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pointlight.h"


MatrixXd PointLight::sampleArea(Sampler sample, RowVector3d hit) {
    MatrixXd tmp(2, 3);
    tmp.block<1,3>(0,0) = pos;
    tmp.block<1,3>(1,0) = pos - hit;
    return tmp;
}

double PointLight::pdfArea() {
    return 0.0;
}

MatrixXd PointLight::SampleSolidAngle(Sampler sample, RowVector3d hit) {
    return sampleArea(sample, hit);
}

double PointLight::pdfSolidAngle(RowVector3d hit) {
    return 0.0;
}
RowVector3d PointLight::getRadiance(RowVector3d hit) {
    return radiance;
}