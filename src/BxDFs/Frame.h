/**
 * @file frame.h
 * @author Matthias Arabian
 * @brief A class to represent a coordinate frame of the given normal
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __FRAME_LIB
#define __FRAME_LIB

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

using Eigen::RowVector3d;

class Frame {
  public:
        RowVector3d n;
        RowVector3d s;
        RowVector3d t;
        Frame(RowVector3d normal) {
            n = normal;
            double invLen;
            if (abs(normal[0]) > abs(normal[1])) {
                invLen = 1 / sqrt(normal[0] * normal[0] + normal[2] * normal[2]);
                t = {normal[2] * invLen, 0, -normal[0] * invLen};
            }
            else {
                invLen = 1 / sqrt(normal[1] * normal[1] + normal[2] * normal[2]);
                t = {0, normal[2] * invLen, -normal[1] * invLen};
            }
            s = t.cross(n);
        }

    
        RowVector3d toLocal(RowVector3d v) {
            // Convert an input vector v from the world fram to the local frame.
            return {v.dot(s), v.dot(t), v.dot(n)};
        }

    
        RowVector3d toWorld(RowVector3d v) {
            // Convert an input vector v from the local fram to the world frame.
            return s * v[0] + t * v[1] + n * v[2];
        }

        double cosTheta(RowVector3d v) {
            // cosine of the angle between vector v and the normal vector of the frame.
            return v[2];
        }
};

#endif