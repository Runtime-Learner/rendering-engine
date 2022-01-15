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
static int intersect_shadowRay(Scene scene, Ray r);
static RowVector3d shade(Scene scene, RowVector3d hitPt, RowVector3d wrWorld, Shape hitObj);

MatrixXd Backward_Raytracing::render(Scene scene, int spp)  {
    
    int resx = scene.resx;
    int resy = scene.resy;
    float fov = scene.fovy;
    Camera cam = scene.camera;
    MatrixXd imgBuffer(resy * resx, 3);

    // calculate height of image plane
    double h_img_plane = tan(fov/180.0 * M_PI/2.0);

    // calculate step size required to travel to adjacent pixel (L/R/U/D)
    double del_dir = h_img_plane / (resy/2.0);

    // calculate basis of plane
    RowVector3d i_dir = cam.dir - cam.eye; i_dir.normalize();  // normal of plane
    RowVector3d i_v = cam.up; i_v.normalize();                // points towards the 'up' direction of the plane w.r.t camera orientation
    RowVector3d i_h = i_v.cross(i_dir); i_h.normalize();  // points towards the 'right' direction of the plane w.r.t camera orientation

    // calculate parameters related to traveling the image plane
    RowVector3d img_plane_centerPt = cam.eye + i_dir * 1;  // center point of image plane. 
    RowVector3d del_v = i_v * del_dir;   // vector used to travel in vertical direction on image plane
    RowVector3d del_h = i_h * del_dir;  // vector used to travel in horizontal direction on image plane

    double seed_v = -resy/2.0;
    double seed_h = -resx/2.0;
    RowVector3d img_plane_initialPt = img_plane_centerPt - del_v * seed_v - del_h * seed_h; // initial point on plane (0,0)
    
    // iterate over all image pixels, generate a ray, and trace it
    RowVector3d color(0, 0, 0);
    for (int x= 0; x < resx; x++) {
        for (int y= 0; y < resy; y++) {
            color = {0, 0, 0};
            for (int s = 0; s < spp; s++) {
                RowVector3d pixel = img_plane_initialPt - del_v * (y + scene.sampler.nextSample()) - del_h * (x + scene.sampler.nextSample());
                RowVector3d rayDir = pixel - cam.eye;
                color += trace(scene, Ray(cam.eye, rayDir));
            }
            color /= spp;
            imgBuffer.block<1,3>(y * resy + x,0) = color.cwiseMin(1).cwiseMax(0); //TODO: scaling factor can be changed to alter ISO
        }
        std::cout << x << "/" << resx << std::endl;
    }
    return imgBuffer;
}

static RowVector3d trace(Scene scene, Ray r) {
    RowVector3d intersection = intersect(scene, r);

    if (intersection[0] > 0) {
        if (scene.lights.size() == 0) {
            Frame frame = scene.geometry[(int)intersection[1]]._p->getFrame(r.o + r.d * intersection[2]);
            return RowVector3d(1, 1, 1) * frame.cosTheta(frame.toLocal(-r.d));
        }
        return shade(scene, r.o + r.d * intersection[2], -r.d, scene.geometry[(int)intersection[1]]);
    }
    return RowVector3d(0,0,0);
}

static RowVector3d shade(Scene scene, RowVector3d hit, RowVector3d wrWorld, Shape hitObj) {

    // add shadow ray
    Light light = scene.selectLight();
    double light_pdf = scene.lightPdf();
    MatrixXd lightInfo = light._p->sampleArea(scene.sampler, hit);
    RowVector3d light_pos = lightInfo.block<1,3>(0,0);
    RowVector3d wiWorld = lightInfo.block<1,3>(1,0);
    double dist_squared = wiWorld.dot(wiWorld);
    Ray shadowRay = Ray(light_pos, -wiWorld, sqrt(dist_squared) - 1e-5);
    int shadowResult = intersect_shadowRay(scene, shadowRay);
    
    if (shadowResult) {
        return RowVector3d(0, 0, 0);
    }

    // initialize variables
    RowVector3d normal = hitObj._p->normal(hit);
    wiWorld.normalize();
    RowVector3d wiLocal = hitObj._p->getFrame(hit).toLocal(wiWorld);
    RowVector3d wrLocal = hitObj._p->getFrame(hit).toLocal(wrWorld);

    // Implement radiance of diffusely reflected light for point light
    RowVector3d Ld = (M_1_PI * 0.25)/(dist_squared) * light._p->getRadiance(hit).array() * hitObj._p->mat._p->eval(hit, wiLocal, wrLocal).array() * light_pdf;

    return Ld;//hitObj._p->mat._p->eval(hit, wrLocal, wrLocal);
}

static int intersect_shadowRay(Scene scene, Ray r) {
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

    size_t n = scene.geometry.size();
    double inf, t, d;
    inf = t = r.max;
    int id = -1;

    for (int i = 0; i < n; i++) {
        d = scene.geometry[i]._p->intersect(r);
        if (d > 0.0 && d < t) { 
            return 1;
        }
    }

    return 0;
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

    size_t n = scene.geometry.size();
    double inf, t, d;
    inf = t = r.max;
    int id = -1;

    for (int i = 0; i < n; i++) {
        d = scene.geometry[i]._p->intersect(r);
        if (d > 0.0 && d < t) { 
            t = d;
            id = i;
        }
    }

    return RowVector3d(t < inf, id, t);
}