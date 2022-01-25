/**
 * @file phongBRDF.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "BxDF.h"
#include "Frame.h"

using Eigen::RowVector3d;

class PhongBRDF : public BxDF::Interface {
    private:
        inline RowVector3d reflect(RowVector3d v) {
            return RowVector3d(-v[0], -v[1], v[2]);
        }
    public:
        RowVector3d kd;
        RowVector3d ks;
        int n;
        double specularSamplingWeight;

        PhongBRDF() {
            kd = RowVector3d(1,1,1);
            ks = RowVector3d(1,1,1);
            n = 1;
            double dAvg = (kd[0] + kd[1] + kd[2]) / 3.0;
            double sAvg = (ks[0] + ks[1] + ks[2]) / 3.0;
            specularSamplingWeight = sAvg / (dAvg + sAvg);
        }

        PhongBRDF(RowVector3d diffuseReflection, RowVector3d specularReflection, int shininess) {
            kd = diffuseReflection;
            ks = specularReflection;
            n = shininess;
            double dAvg = (kd[0] + kd[1] + kd[2]) / 3.0;
            double sAvg = (ks[0] + ks[1] + ks[2]) / 3.0;
            specularSamplingWeight = sAvg / (dAvg + sAvg);
        }

        //TODO: document
        RowVector3d eval(RowVector3d hitPt, RowVector3d wi, RowVector3d wr) {
            Frame frame = Frame({0,0,1});
            return kd * M_1_PI + ks * (n + 2) * M_1_PI * pow(std::max(wi.dot(reflect(wr)), 0.0), n) * frame.cosTheta(wi);
        }

        //TODO: document
        RowVector3d sample(Sampler sampler, RowVector3d wr) {
            if (sampler.nextSample() > specularSamplingWeight) {
            return Sampler::cosineSampleHemisphere(sampler.next2D());
            }
            else {
            RowVector3d wi_lobe = Sampler::uniformSamplePhongLobe(sampler.next2D(), n);
            return Frame(reflect(wr)).toWorld(wi_lobe);
            }
        }

        //TODO: document
        double pdf(RowVector3d wi, RowVector3d wr) {
            //convert wi to lobe local frame
            RowVector3d wi_lobe = Frame(reflect(wr)).toLocal(wi);
            return (1 - specularSamplingWeight) * Sampler::cosineHemispherePdf(wi) + Sampler::uniformPhongLobePdf(wi_lobe, n) * (specularSamplingWeight);
        }


};