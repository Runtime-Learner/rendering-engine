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

#ifndef __MATRIX_OP_LIB
#define __MATRIX_OP_LIB

#include "matrix_ops.h"


extern MatrixXd matrix_dot(MatrixXd a, MatrixXd b) {
    if (b.rows() > 1) {
        return a.col(0).array() * b.col(0).array() + a.col(1).array() * b.col(1).array() + a.col(2).array() * b.col(2).array();
    }
    else {
        return a.col(0) * b(0) + a.col(1) * b(1) + a.col(2) * b(2);
    }
}

extern MatrixXd matrix_cross(MatrixXd a, MatrixXd b) {
    // a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1
    MatrixXd result(a.rows(), a.cols());

    if (b.rows() > 1) {
        result.col(0) <<  a.col(1).array().cwiseProduct(b.col(2).array()) - a.col(2).array().cwiseProduct(b.col(1).array());
        result.col(1) << a.col(2).array().cwiseProduct(b.col(0).array()) - a.col(0).array().cwiseProduct(b.col(2).array());
        result.col(2) << a.col(0).array().cwiseProduct(b.col(1).array()) - a.col(1).array().cwiseProduct(b.col(0).array());
    }
    else {
        result.col(0) << a.col(1) * b(2) - a.col(2) * b(1);
        result.col(1) << a.col(2) * b(0) - a.col(0) * b(2);
        result.col(2) << a.col(0) * b(1) - a.col(1) * b(0);
    }
    
    return result;
}

extern MatrixXd matrix_rowMulWithScalar(MatrixXd a, MatrixXd b) {
    MatrixXd result(a.rows(), a.cols());

    if (b.cols() > 1 || b.rows() != a.rows()) {
        throw ; //TODO: add more descriptive throw
    }
    else {
        for (int col = 0; col < a.cols(); col++) {
            result.col(col) << a.col(col).array() * b.array();
        }
    }
    
    return result;
}

extern MatrixXd matrix_makeMatrixFromArrAndMultiplier(RowVector3d a, MatrixXd b) {
    MatrixXd result(b.rows(), a.cols());
    for (int col = 0; col < a.cols(); col++) {
        result.col(col) << a(col) * b.array();
    }
    return result;
}

extern MatrixXd matrix_rowSumWithVector(MatrixXd a, RowVector3d b) {
    MatrixXd result(a.rows(), a.cols());

    if (b.rows() > 1 || b.cols() != a.cols()) {
        throw ; //TODO: add more descriptive throw
    }
    else {
        for (int col = 0; col < a.cols(); col++) {
            result.col(col) << a.col(col).array() + b(col);
        }
    }
    return result;
}

#endif