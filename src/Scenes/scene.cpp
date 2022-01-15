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

#include <iostream>
#include <cstring>

#include <vector>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "../Ray/ray.cpp"
#include "../Shapes/Shapes.h"
#include "../Cameras/camera.cpp"
#include "../Lights/Lights.h"
#include "../BxDFs/sampler.h"

using Eigen::RowVector3d;


class Scene {
    public:
        std::vector<Shape> geometry;
        std::vector<Light> lights;
        Camera camera;
        float fovy; //field of view in vertical direction
        int resx;   //# pixels horizontally
        int resy;   //# pixels vertically
        Sampler sampler;

        Scene(std::vector<Shape> g, std::vector<Light> l, Camera c, float fov, int width, int height) {
            geometry = g;
            lights = l;
            camera = c;
            fovy = fov;
            resx = width;
            resy = height;
            sampler = Sampler();
        }

        Light selectLight() {
            double index = (sampler.nextSample() * (lights.size()));
            
            return lights[(int)index];
        }

        double lightPdf() {
            return 1.0 / std::max(1, (int)lights.size());
        }


        static std::vector<Shape> loadObjFile(std::string filepath, int scalingFactor) {
            std::vector<Shape> geometry;
            std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
            std::vector< RowVector3d > temp_vertices;
            std::vector< RowVector2d > temp_uvs;
            std::vector< RowVector3d > temp_normals;
            std::cout << "loading obj file \'" << filepath << "\'" << std::endl;
            FILE * file;
            fopen_s(&file, filepath.c_str(), "r");
            if( file == NULL ){
                printf("Impossible to open the file !\n");
                return geometry;
            }

            while( 1 ){

                char lineHeader[128];
                // read the first word of the line
                int res = fscanf(file, "%s", lineHeader);
                if (res == EOF)
                    break; // EOF = End Of File. Quit the loop.

                    // else : parse lineHeader
                if ( strcmp( lineHeader, "v" ) == 0 ){
                    RowVector3d vertex;
                    fscanf(file, "%lf %lf %lf\n", &vertex[0], &vertex[1], &vertex[2] );
                    temp_vertices.push_back(vertex * scalingFactor);
                }
                // else if ( strcmp( lineHeader, "vt" ) == 0 ){
                //     glm::vec2 uv;
                //     fscanf(file, "%f %f\n", &uv.x, &uv.y );
                //     temp_uvs.push_back(uv);
                // }
                // else if ( strcmp( lineHeader, "vn" ) == 0 ){
                //     glm::vec3 normal;
                //     fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                //     temp_normals.push_back(normal);
                // }
                else if ( strcmp( lineHeader, "f" ) == 0 ) {
                    std::string vertex1, vertex2, vertex3;
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                    if (matches != 3){
                        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                        return geometry;
                    }
                    // int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                    // if (matches != 9){
                    //     printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    //     return false;
                    // }
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    geometry.push_back(new Triangle(temp_vertices[vertexIndex[0] - 1], temp_vertices[vertexIndex[1] - 1], temp_vertices[vertexIndex[2] - 1]));
                    // uvIndices    .push_back(uvIndex[0]);
                    // uvIndices    .push_back(uvIndex[1]);
                    // uvIndices    .push_back(uvIndex[2]);
                    // normalIndices.push_back(normalIndex[0]);
                    // normalIndices.push_back(normalIndex[1]);
                    // normalIndices.push_back(normalIndex[2]);
                    // std::cout << temp_vertices[vertexIndex[0]] << temp_vertices[vertexIndex[1]] << temp_vertices[vertexIndex[2]] << std::endl;
                }
            }
            fclose(file);
            std::cout << "done loading obj file" << std::endl;
            std::cout << geometry.size() << std::endl;
            return geometry;
        }
};
#endif