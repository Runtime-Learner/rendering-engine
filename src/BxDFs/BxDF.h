
#ifndef __BxDF_INTERFACE_RENDERER
#define  __BxDF_INTERFACE_RENDERER

#include <vector>
#include <memory>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "sampler.h"

using Eigen::RowVector3d;
using std::vector;

class BxDF {
    public:
        struct Interface {
            virtual RowVector3d eval(RowVector3d hitPt, RowVector3d wi, RowVector3d wr) = 0;
            virtual double sample(Sampler sampler, RowVector3d wr)             = 0;
            virtual double pdf(RowVector3d wi, RowVector3d wr)             = 0;
            // TODO: add support for SIMD matrix_intersect function

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