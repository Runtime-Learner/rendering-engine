/**
 * @file Shapes/sphere.cpp
 * @author Matthias Arabian
 * @brief sphere class used as primitive in rendering system
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "sphere.h"

Sphere::Sphere(RowVector3d center, double radius) {
    c = center;
    r = radius;
    mat = new DiffuseBRDF();
}

Sphere::Sphere(RowVector3d center, double radius, BxDF bxdf) {
    c = center;
    r = radius;
    mat = bxdf;
}

RowVector3d Sphere::normal(RowVector3d point) {
    RowVector3d n = point - c;
    n.normalize();
    return n;
}

double Sphere::intersect(Ray ray) {
    double A = ray.d.dot(ray.d);
    double B = 2 * (ray.o - c).dot(ray.d);
    double C = (ray.o - c).dot((ray.o - c)) - r * r;
    double discriminant = B * B - 4 * A * C;
    if (discriminant < 0.0) {
        return 0;
    }
    else {
        double t1 = (-B - sqrt(discriminant)) / (2 * A);
        if (t1 > 0.0) {
            return t1;
        }
        double t2 = (-B + sqrt(discriminant)) / (2 * A);
        if (t2 > 0.0)
            return t2;
        else
            return 0;
    }
}

// MatrixXd Sphere::intersect_matrix(MatrixXd rayDir_mat, RowVector3d initialPt) {
//     return rayDir_mat; //TODO: implement
// }
