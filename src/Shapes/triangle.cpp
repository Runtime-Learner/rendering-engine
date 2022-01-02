/**
 * @file Shapes/triangle.cpp
 * @author Matthias Arabian
 * @brief triangle class used for testing of rendering system
 * @version 0.1
 * @date 2021-12-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "triangle.h"

Triangle::Triangle(RowVector3d a, RowVector3d b, RowVector3d c) {
v0 = a;
v1 = b;
v2 = c;
}

RowVector3d Triangle::normal() {
    RowVector3d vec = v0.cross(v1);
    vec.normalize();
    return vec;
}

double Triangle::intersect(Ray r) {
    // std::cout << "intersect start" << std::endl;
    RowVector3d e1 = v1 - v0;
    RowVector3d e2 = v2 - v0;
    // std::cout << e1 << std::endl;
    // std::cout << e2 << std::endl;

    RowVector3d h = r.d.cross(e2);
    // std::cout << h << std::endl;

    double a = e1.dot(h);
    // std::cout << a << std::endl;
    
    if (a > -1.0e-6 && a < 1.0e-6) {
        return 0.0;
    }
        
    double f = 1.0/a;
    // std::cout << f << std::endl;
    RowVector3d s = r.o - v0;
    // std::cout << s << std::endl;
    double u = f * s.dot(h);
    // std::cout << u << std::endl;

    if (u < 0.0 || u > 1.0) {
        return 0.0;
    }

    RowVector3d q = s.cross(e1);
    // std::cout << q << std::endl;
    double v = f * r.d.dot(q);
    // std::cout << v << std::endl;

    if (v < 0.0 || u + v > 1.0) {
        return 0.0;
    }
    double t = f * e2.dot(q);
    // std::cout << t << std::endl;

    return t;
}