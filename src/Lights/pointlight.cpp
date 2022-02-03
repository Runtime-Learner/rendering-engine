/**
 * @file pointlight.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#include "pointlight.h"


MatrixXd PointLight::sampleArea(Sampler sampler, RowVector3d hit) {
    MatrixXd tmp(3, 3);
    tmp.block<1,3>(0,0) = pos;
    tmp.block<1,3>(1,0) = (pos - hit).normalized();
    tmp.block<1,3>(2,0) = pos - hit;
    return tmp;
}

double PointLight::pdfArea() {
    return 0.0;
}

MatrixXd PointLight::SampleSolidAngle(Sampler sampler, RowVector3d hit) {
    return sampleArea(sampler, hit);
}

double PointLight::pdfSolidAngle(RowVector3d hit) {
    return 0.0;
}
RowVector3d PointLight::getRadiance(RowVector3d hit) {
    return radiance;
}