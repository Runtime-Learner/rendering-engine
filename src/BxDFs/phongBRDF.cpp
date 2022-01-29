/**
 * @file phongBRDF.cpp
 * @author Matthias Arabian
 * @brief phong BRDF implementation
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

class PhongBRDF : public BxDF::Interface {
    private:
        //TODO: put this function somewhere better

        /**
         * @brief reflect the vector across the z axis
         * 
         * @param v vector in local frame
         * @return RowVector3d reflected vector v'
         */
        inline RowVector3d reflect(RowVector3d v) {
            return RowVector3d(-v[0], -v[1], v[2]);
        }

    public:
        RowVector3d kd;
        RowVector3d ks;
        int n;
        double specularSamplingWeight;

        /**
         * @brief Construct a new PhongBRDF object
         * This object will have a 50/50 ratio of diffuse and specular behavior. It will not be very shiny.
         * 
         */
        PhongBRDF() {
            kd = RowVector3d(1,1,1);
            ks = RowVector3d(1,1,1);
            n = 1;
            double dAvg = (kd[0] + kd[1] + kd[2]) / 3.0;
            double sAvg = (ks[0] + ks[1] + ks[2]) / 3.0;
            specularSamplingWeight = sAvg / (dAvg + sAvg);
        }

        /**
         * @brief Construct a new PhongBRDF object
         * 
         * @param diffuseReflection RGB diffuse albedo
         * @param specularReflection RGB specular albedo
         * @param shininess how shiny the specular reflections will look
         */
        PhongBRDF(RowVector3d diffuseReflection, RowVector3d specularReflection, int shininess) {
            kd = diffuseReflection;
            ks = specularReflection;
            n = shininess;
            double dAvg = (kd[0] + kd[1] + kd[2]) / 3.0;
            double sAvg = (ks[0] + ks[1] + ks[2]) / 3.0;
            specularSamplingWeight = sAvg / (dAvg + sAvg);
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
            return kd * M_1_PI + ks * (n + 2) * M_1_PI * pow(std::max(wi.dot(reflect(wr)), 0.0), n) * frame.cosTheta(wi);
        }

        /**
         * @brief BxDF sampling method. Used to get a direction vector wi to continue the light path
         * 
         * @param sampler sampler object used for random number generation
         * @param wr outgoing light direction (local coordinates)
         * @return RowVector3d direction vector wi, in world coordinates.
         */
        RowVector3d sample(Sampler sampler, RowVector3d wr) {
            if (sampler.nextSample() > specularSamplingWeight) {
            return Sampler::cosineSampleHemisphere(sampler.next2D());
            }
            else {
            RowVector3d wi_lobe = Sampler::uniformSamplePhongLobe(sampler.next2D(), n);
            return Frame(reflect(wr)).toWorld(wi_lobe);
            }
        }

        /**
         * @brief returns the probability of sampling wi given wr, when using the BxDF sampling method.
         * 
         * @param wi incoming light direction (local coordinates)
         * @param wr outgoing light direction (local coordinates)
         * @return double probability of sampling wi given wr, when using the BxDF sampling method.
         */
        double pdf(RowVector3d wi, RowVector3d wr) {
            //convert wi to lobe local frame
            RowVector3d wi_lobe = Frame(reflect(wr)).toLocal(wi);
            return (1 - specularSamplingWeight) * Sampler::cosineHemispherePdf(wi) + Sampler::uniformPhongLobePdf(wi_lobe, n) * (specularSamplingWeight);
        }


};