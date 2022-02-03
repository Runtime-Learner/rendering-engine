/**
 * @file BxDF.h
 * @author Matthias Arabian
 * @brief interface class inherited by all BxDF classes. Defines all ways the renderer can interact with BxDF objects.
 * @version 0.1
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


#ifndef __BxDF_INTERFACE_RENDERER
#define  __BxDF_INTERFACE_RENDERER

#ifdef _MSC_VER
#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include <corecrt_math_defines.h>
#endif
#endif

#include <vector>
#include <memory>
#include <math.h>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "sampler.h"

using Eigen::RowVector3d;
using std::vector;

class BxDF {
    public:
        struct Interface {
            /**
             * @brief Evaluate the light outgoing from point hitPt towards wr
             * 
             * @param hitPt the point at which light is incoming/outgoing
             * @param wi the incoming light direction (local coordinates)
             * @param wr the outgoing light direction (local coordinates)
             * @return RowVector3d the % of light outgoing from point hitPt towards wr (R, G, B)
             */
            virtual RowVector3d eval(RowVector3d hitPt, RowVector3d wi, RowVector3d wr) = 0;

            /**
             * @brief BxDF sampling method. Used to get a direction vector wi to continue the light path
             * 
             * @param sampler sampler object used for random number generation
             * @param wr outgoing light direction (local coordinates)
             * @return RowVector3d direction vector wi, in world coordinates.
             */
            virtual RowVector3d sample(Sampler sampler, RowVector3d wr)             = 0;

            /**
             * @brief returns the probability of sampling wi given wr, when using the BxDF sampling method.
             * 
             * @param wi incoming light direction (local coordinates)
             * @param wr outgoing light direction (local coordinates)
             * @return double probability of sampling wi given wr, when using the BxDF sampling method.
             */
            virtual double pdf(RowVector3d wi, RowVector3d wr)             = 0;

            Interface()  {}
            virtual ~Interface()                          = default;
        };

        std::shared_ptr<Interface> _p;
        BxDF() {
            _p = nullptr;
        }
        BxDF(Interface* p) : _p(p) {

        }
};

#endif