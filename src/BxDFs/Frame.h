/**
 * @file frame.h
 * @author Matthias Arabian
 * @brief A class to represent a coordinate frame of the given normal
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

        /**
         * @brief Construct a new Frame object using the normal as the z axis
         * 
         * @param normal the z axis of our new frame of reference
         */
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

        /**
         * @brief Convert a vector from world coordinates into local coordinates
         * 
         * @param v vector in world coordinates
         * @return RowVector3d vector in local coordinates
         */
        RowVector3d toLocal(RowVector3d v) {
            // Convert an input vector v from the world fram to the local frame.
            return {v.dot(s), v.dot(t), v.dot(n)};
        }

        /**
         * @brief Convert a vector from local coordinates into world coordinates
         * 
         * @param v vector in local coordinates
         * @return RowVector3d vector in world coordinates
         */
        RowVector3d toWorld(RowVector3d v) {
            // Convert an input vector v from the local fram to the world frame.
            return s * v[0] + t * v[1] + n * v[2];
        }

        /**
         * @brief Return the cosine of the angle between vector v and the normal vector of the frame.
         * 
         * @param v vector in local coordinates
         * @return double cosine of the angle between vector v and the normal vector of the frame.
         */
        double cosTheta(RowVector3d v) {
            return v[2];
        }
};

#endif