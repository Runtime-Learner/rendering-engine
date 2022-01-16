/**
 * @file Renderers/renderer_matrix.cpp
 * @author Matthias Arabian
 * @brief renderer class for backward ray tracing
 * @version 0.1
 * @date 2021-12-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "renderer_matrix.h"
#include "../Shapes/matrix_ops.h"

static MatrixXd intersect_matrix(Scene scene, MatrixXd rayDir_mat, RowVector3d initialPt);
static MatrixXd trace_matrix(Scene scene, MatrixXd rayDir_mat, RowVector3d initialPt);

MatrixXd Backward_Raytracing_Matrix::render(Scene scene, int spp)  {
    
    int resx = scene.resx;
    int resy = scene.resy;
    float fov = scene.fovy;
    Camera cam = scene.camera;
    MatrixXd imgBuffer(resy * resx, 3);
    imgBuffer = imgBuffer * 0; //initialize all values to 0 in image

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

    float seed_v = -resy/2.0;
    float seed_h = -resx/2.0;
    RowVector3d img_plane_initialPt = img_plane_centerPt - del_v * seed_v - del_h * seed_h; // initial point on plane (0,0)
    
    // generate matrix of del_factors
    MatrixXd m = Eigen::RowVectorXd::LinSpaced(resx, 0, resx - 1).replicate(resy, 1);
    MatrixXd mat_v = m.reshaped(resx * resy, 1);
    MatrixXd mat_h =  m.transpose().reshaped(resx * resy, 1);
 
    MatrixXd pixelBase = img_plane_initialPt.replicate(resy * resx, 1);
    
    // iterate over all image pixels, generate a ray, and trace it
    MatrixXd rayPos_mat(resy * resx, 3);
    for (int s = 0; s < spp; s++) {
        rayPos_mat = pixelBase - matrix_makeMatrixFromArrAndMultiplier(del_v, mat_v + scene.sampler.nextMatrix(resy * resx, 1)) - matrix_makeMatrixFromArrAndMultiplier(del_h, mat_h + scene.sampler.nextMatrix(resy * resx, 1));
        imgBuffer += trace_matrix(scene, matrix_rowSumWithVector(rayPos_mat, -cam.eye), cam.eye);
        std::cout << s << "/" << spp << std::endl;
    }

    return imgBuffer / spp;
}

////////////////////////////////////////////////
// Matrix intersection code
///////////////////////////////////////////////
/**
MatrixXd shade_matrix(Scene scene, MatrixXd hit_mat, MatrixXd wrWorld_mat, MatrixXd shapeId_mat) {

    // add shadow ray
    Light light = scene.selectLight();

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
    double light_pdf = scene.lightPdf();
    RowVector3d normal = hitObj._p->normal(hit);
    wiWorld.normalize();
    RowVector3d wiLocal = hitObj._p->getFrame(hit).toLocal(wiWorld);
    RowVector3d wrLocal = hitObj._p->getFrame(hit).toLocal(wrWorld);

    // Implement radiance of diffusely reflected light for point light
    RowVector3d Ld =  (M_1_PI * 0.25)/(dist_squared) * light._p->getRadiance(hit).array() * hitObj._p->mat._p->eval(hit, wiLocal, wrLocal).array() * light_pdf;

    return Ld;//hitObj._p->mat._p->eval(hit, wrLocal, wrLocal);
}
**/
static MatrixXd trace_matrix(Scene scene, MatrixXd rayDir_mat, RowVector3d initialPt) {
    MatrixXd intersection_data = intersect_matrix(scene, rayDir_mat, initialPt); // [0:2] hit dist [3] obj id
    MatrixXd imgData(rayDir_mat.rows(), rayDir_mat.cols());
    for (int row = 0; row < rayDir_mat.rows(); row++) {
        if (intersection_data(row, 1) == -1) {
            imgData.block<1, 3>(row, 0) = RowVector3d({0, 0, 0});
        } else {
            if (scene.lights.size() == 0) {
                Frame frame = scene.geometry[intersection_data(row, 1)]._p->getFrame(initialPt + rayDir_mat.row(row) * intersection_data(row, 0));
                return RowVector3d(1, 1, 1) * frame.cosTheta(frame.toLocal(-rayDir_mat.row(row)));
            }
            imgData.block<1, 3>(row, 0) = Backward_Raytracing::shade(scene, initialPt + rayDir_mat.row(row) * intersection_data(row, 0), {0,0,0}/**-rayDir_mat.row(row) **/, scene.geometry[intersection_data(row, 1)]);
        }
    }
    return imgData;
}

// static MatrixXd trace_matrix(Scene scene, MatrixXd rayDir_mat, RowVector3d initialPt) {
//     MatrixXd intersection_data = intersect_matrix(scene, rayDir_mat, initialPt); // [0:2] hit dist [3] obj id
//     MatrixXd imgData(rayDir_mat.rows(), rayDir_mat.cols());
//     for (int row = 0; row < rayDir_mat.rows(); row++) {
//         if (intersection_data(row, 1) == -1) {
//             imgData.block<1, 3>(row, 0) = RowVector3d({0, 0, 0});
//         } else {
//             if (scene.lights.size() == 0) {
//                 Frame frame = scene.geometry[intersection_data(row, 1)]._p->getFrame(initialPt + rayDir_mat.row(row) * intersection_data(row, 0));
//                 return RowVector3d(1, 1, 1) * frame.cosTheta(frame.toLocal(-rayDir_mat.row(row)));
//             }
//             imgData.block<1, 3>(row, 0) = Backward_Raytracing::shade(scene, initialPt + rayDir_mat.row(row) * intersection_data(row, 0), -rayDir_mat.row(row), scene.geometry[intersection_data(row, 1)]);
//         }
//     }
//     return imgData;
// }


// return matrix w/ cols [0] hit dist [1] obj id
static MatrixXd intersect_matrix(Scene scene, MatrixXd rayDir_mat, RowVector3d initialPt) {
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
    MatrixXd t(rayDir_mat.rows(), 1); t.fill(1e20);
    MatrixXd id(rayDir_mat.rows(), 1); id.fill(-1);
    MatrixXd d;
    
    std::cout << "start intersection" << std::endl;
    for (int i = 0; i < n; i++) {
        
        d = scene.geometry[i]._p->intersect_matrix(rayDir_mat, initialPt);
        std::cout << d.rows() << ", " << d.cols() << std::endl;
        auto cond = (d.array() > 0.0 && d.array() < t.array());
        id = (cond).select(i, id);
        t = (cond).select(d, t);
    }
    std::cout << "end intersection" << std::endl;


    MatrixXd intersectionData(rayDir_mat.rows(), 2);
    intersectionData.col(0) << t;
    intersectionData.col(1) << id;
    return intersectionData;
}