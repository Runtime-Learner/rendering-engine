/**
 * @file scene.h
 * @author Matthias Arabian
 * @brief 
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __SCENE_RENDERER
#define __SCENE_RENDERER

#include <vector>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../Shapes/Shapes.h"
#include "../Cameras/camera.cpp"
#include "../Lights/pointlight.cpp"

using Eigen::RowVector3d;


class Scene {
    public:
        std::vector<Shape> geometry;
        PointLight light;    //point light
        Camera camera;
        float fovy; //field of view in vertical direction
        int resx;   //# pixels horizontally
        int resy;   //# pixels vertically

        Scene(std::vector<Shape> g, PointLight l, Camera c, float fov, int width, int height) {
            geometry = g;
            light = l;
            camera = c;
            fovy = fov;
            resx = width;
            resy = height;
        }
};
#endif