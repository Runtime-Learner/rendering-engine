/**
 * @file matrix_ops.h
 * @author Matthias Arabian
 * @brief functions to run basic vector operations on a matrix full of vectors
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright (c) 2022 
 * This file is part of SimpleEngine. SimpleEngine is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
 * SimpleEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details. 
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#ifndef __MATRIX_OP_LIB_H
#define __MATRIX_OP_LIB_H

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

using Eigen::RowVector3d;
using Eigen::MatrixXd;

extern MatrixXd matrix_dot(MatrixXd a, MatrixXd b);
extern MatrixXd matrix_cross(MatrixXd a, MatrixXd b);
extern MatrixXd matrix_rowMulWithScalar(MatrixXd a, MatrixXd b);
extern MatrixXd matrix_makeMatrixFromArrAndMultiplier(RowVector3d a, MatrixXd b);
extern MatrixXd matrix_rowSumWithVector(MatrixXd a, RowVector3d b);
#endif