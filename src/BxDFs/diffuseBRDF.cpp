/**
 * @file diffuseBRDF.cpp
 * @author Matthias Arabian
 * @brief diffuse BRDF implementation. 
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

#include "BxDF.h"
#include "Frame.h"

class DiffuseBRDF : public BxDF::Interface {
    public:
        RowVector3d albedo;

        /**
         * @brief Construct a new DiffuseBRDF object with RGB albedo [1,1,1]
         * 
         */
        DiffuseBRDF() {
            albedo = RowVector3d(1,1,1);
        }

        /**
         * @brief Construct a new DiffuseBRDF object
         * 
         * @param color the RGB albedo of the object. All three must be in the range [0, 1] for physically based rendering
         */
        DiffuseBRDF(RowVector3d color) {
            albedo = color;
        }

        /**
         * @brief Evaluate the light outgoing from point hitPt towards wr
         * 
         * @param hitPt the point at which light is incoming/outgoing
         * @param wi the incoming light direction (local coordinates)
         * @param wr the outgoing light direction (local coordinates)
         * @return RowVector3d the % of light outgoing from point hitPt towards wr (R, G, B)
         */
        RowVector3d eval(RowVector3d hitPt, RowVector3d wi, RowVector3d wr) {
            Frame frame = Frame({0,0,1});
            return albedo * M_1_PI * frame.cosTheta(wi);
        }

        /**
         * @brief BxDF sampling method. Used to get a direction vector wi to continue the light path
         * 
         * @param sampler sampler object used for random number generation
         * @param wr outgoing light direction (local coordinates)
         * @return RowVector3d direction vector wi, in world coordinates.
         */
        RowVector3d sample(Sampler sampler, RowVector3d wr) {
            RowVector3d val(0,0,0);
            RowVector3d wi = Sampler::cosineSampleHemisphere(sampler.next2D());
            return wi;
        }

        /**
         * @brief returns the probability of sampling wi given wr, when using the BxDF sampling method.
         * 
         * @param wi incoming light direction (local coordinates)
         * @param wr outgoing light direction (local coordinates)
         * @return double probability of sampling wi given wr, when using the BxDF sampling method.
         */
        double pdf(RowVector3d wi, RowVector3d wr) {
            return Sampler::cosineHemispherePdf(wi);
        }


};