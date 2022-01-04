/**
 * @file Renderers/renderer.cpp
 * @author Matthias Arabian
 * @brief renderer class for backward ray tracing
 * @version 0.1
 * @date 2021-12-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "renderer.h"

static RowVector3d trace(Scene scene, Ray r);
static RowVector3d intersect(Scene scene, Ray r);
static RowVector3d shade(Scene scene, RowVector3d hitPt, Triangle hitObj);

MatrixXd Backward_Raytracing::render(Scene scene)  {
    
    int resx = scene.resx;
    int resy = scene.resy;
    float fov = scene.fovy;
    Camera cam = scene.camera;
    MatrixXd imgBuffer(resy * resx, 3);

    // calculate height of image plane
    float h_img_plane = tan(fov/180.0 * M_PI/2.0);

    // calculate step size required to travel to adjacent pixel (L/R/U/D)
    float del_dir = h_img_plane / (resy/2.0);

    // calculate basis of plane
    RowVector3d i_dir = cam.dir - cam.eye; i_dir.normalize();  // normal of plane
    RowVector3d i_v = cam.up; i_v.normalize();                // points towards the 'up' direction of the plane w.r.t camera orientation
    RowVector3d i_h = i_v.cross(i_dir); i_h.normalize();  // points towards the 'right' direction of the plane w.r.t camera orientation

    // calculate parameters related to traveling the image plane
    RowVector3d img_plane_centerPt = cam.eye + i_dir * 1;  // center point of image plane. 
    RowVector3d del_v = i_v * del_dir;   // vector used to travel in vertical direction on image plane
    RowVector3d del_h = i_h * del_dir;  // vector used to travel in horizontal direction on image plane

    float seed_v = 0.5 - resy/2.0;
    float seed_h = 0.5 - resx/2.0;
    RowVector3d img_plane_initialPt = img_plane_centerPt - del_v * seed_v - del_h * seed_h; // initial point on plane (0,0)
    
    // iterate over all image pixels, generate a ray, and trace it
    RowVector3d color(0, 0, 0);
    for (int x= 0; x < resx; x++) {
        color = {0, 0, 0};
        for (int y= 0; y < resy; y++) {
            RowVector3d pixel = img_plane_initialPt - del_v * y - del_h * x;
            RowVector3d rayDir = pixel - cam.eye;
            color = trace(scene, Ray(cam.eye, rayDir));
            imgBuffer.block<1,3>(y * resy + x,0) = color.cwiseMin(1).cwiseMax(0); //TODO: scaling factor can be changed to alter ISO
        }
    }
    return imgBuffer;
}

static RowVector3d trace(Scene scene, Ray r) {
    RowVector3d intersection = intersect(scene, r);
    if (intersection[0] > 0) {
        return shade(scene, r.o + r.d * intersection[2], scene.geometry[intersection[1]]);
    }
    return RowVector3d(0,0,0);
}

static RowVector3d shade(Scene scene, RowVector3d hit, Triangle hitObj) {
    // add shadow ray
    RowVector3d shadowRay_dir = hit - scene.light.pos;
    RowVector3d shadowRay_origin = scene.light.pos;
    double dist_squared = shadowRay_dir.dot(shadowRay_dir);
    Ray shadowRay = Ray(shadowRay_origin, shadowRay_dir, sqrt(dist_squared) - 1e-5);
    RowVector3d shadowResult = intersect(scene, shadowRay);
    
    if (shadowResult[0] == 1) {
        return RowVector3d(0, 0, 0);
    }

    // initialize variables
    double albedo = 1;
    RowVector3d normal = hitObj.normal(); normal.normalize();
    RowVector3d light_dir = -shadowRay_dir; light_dir.normalize();

    // Implement radiance of diffusely reflected light for point light
    RowVector3d Ld = (albedo * M_1_PI * M_1_PI * 0.25)/(dist_squared) * scene.light.radiance.array() * std::max(normal.dot(light_dir), 0.0) * hitObj.mat.c.array();

    return Ld;
}

static RowVector3d intersect(Scene scene, Ray r) {
    /**
    Method to intersect all objects in the scene
    Parameters:
        scene: scene to render.
        ray: ray to trace.
    Returns:
      (has_hit, hit_object_id, distance_to_object)
      has_hit is 0 if there is not hit, else it is 1
      id is the idx of the scene object hit
      t is the ray parameter (recall a ray is o + td) at which
        a hit is found
    **/

    int n = scene.geometry.size();
    double inf, t, d;
    inf = t = r.max;
    int id = -1;

    for (int i = 0; i < n; i++) {
        d = scene.geometry[i].intersect(r);
        if (d > 0.0 && d < t) { 
            t = d;
            id = i;
        }
    }

    return RowVector3d(t < inf, id, t);
}