/**
 * @file pointlight.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
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