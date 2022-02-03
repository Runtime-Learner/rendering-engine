/**
 * @file quadlight.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#include "quadlight.h"


MatrixXd QuadLight::sampleArea(Sampler sampler, RowVector3d hit) {
    MatrixXd tmp(3, 3);

    bool trig = area1 / area >= sampler.nextSample();
    RowVector2d uv = Sampler::uniformSampleTriangle(sampler.next2D());
    if (trig) {
        tmp.block<1,3>(0,0) = v0 * (1 - uv[0] - uv[1]) + v1 * uv[0] + v2 * uv[1]; // position
        tmp.block<1,3>(1,0) = ((v1 - v0).cross(v2 - v0)).normalized();
    }
    else {
        tmp.block<1,3>(0,0) = v0 * (1 - uv[0] - uv[1]) + v2 * uv[0] + v3 * uv[1]; // position
        tmp.block<1,3>(1,0) = ((v2 - v0).cross(v3 - v0)).normalized();
    }

    tmp.block<1,3>(2,0) = tmp.block<1,3>(0,0) - hit;
    return tmp;
}

double QuadLight::pdfArea() {
    return 1.0 / area;
}

MatrixXd QuadLight::SampleSolidAngle(Sampler sampler, RowVector3d hit) {
    return sampleArea(sampler, hit);
}

double QuadLight::pdfSolidAngle(RowVector3d hit) {
    return pdfArea();
}
RowVector3d QuadLight::getRadiance(RowVector3d hit) {
    return radiance;
}