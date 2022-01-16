/**
 * @file matrix_ops.h
 * @author Matthias Arabian
 * @brief functions to run basic vector operations on a matrix full of vectors
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
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