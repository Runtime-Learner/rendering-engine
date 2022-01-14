/**
 * @file box.cpp
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * intersection code comes from:
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
 */

#include "box.h"

Box::Box(RowVector3d v1, RowVector3d v2) {
    //TODO:implement
}

Box::Box(RowVector3d v1, RowVector3d v2, BxDF bxdf) {
    //TODO:implement
}

RowVector3d Box::normal(RowVector3d point) {
    //TODO:implement
}

//TODO:fix
double Box::intersect(Ray r) 
{ 
    // double tmin, tmax, tymin, tymax, tzmin, tzmax; 
 
    // tmin = (bounds[r.sign[0]].x - r.o[0]) * r.invDir[0]; 
    // tmax = (bounds[1-r.sign[0]].x - r.o[0]) * r.invDir[0]; 
    // tymin = (bounds[r.sign[1]].y - r.o[1]) * r.invDir[1]; 
    // tymax = (bounds[1-r.sign[1]].y - r.o[1]) * r.invDir[1]; 
 
    // if ((tmin > tymax) || (tymin > tmax)) 
    //     return false; 
    // if (tymin > tmin) 
    //     tmin = tymin; 
    // if (tymax < tmax) 
    //     tmax = tymax; 
 
    // tzmin = (bounds[r.sign[2]].z - r.o[2]) * r.invDir[2]; 
    // tzmax = (bounds[1-r.sign[2]].z - r.o[2]) * r.invDir[2]; 
 
    // if ((tmin > tzmax) || (tzmin > tmax)) 
    //     return false; 
    // if (tzmin > tmin) 
    //     tmin = tzmin; 
    // if (tzmax < tmax) 
    //     tmax = tzmax; 
 
    // return true; 
} 