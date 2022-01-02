#include <iostream>
#include <unistd.h>
#include <vector>
#include "eigen3/Eigen/Core"
#include "rendering_engine.h"
 
using Eigen::RowVector3d;
using Eigen::MatrixXd;

Scene getTriangleScene(int width, int height);
void printHit(MatrixXd img, int width, int height);

int main(int argc, char* argv[])
{
	int width, height;

  	// validate user parameters
	if (argc != 3 || argv[1] == NULL || argv[2] == NULL) {
		std::cout << "Invalid parameters: ./app <width> <height>\n";
		std::cout << "Defaulting to 5 x 5 image\n";
		width = 5;
		height = 5;
	}
	else {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}


	if (width <= 0 || height <= 0) {
		std::cout << "invalid width or height parameter. Must be an integer larger than 0.\n";
		return 0;
	}
  Backward_Raytracing renderer;
  Scene s = getTriangleScene(width, height);
  MatrixXd c = renderer.render(s); 
  printHit(c, s.resx, s.resy);
}



Scene getTriangleScene(int width, int height) {
  std::vector<Triangle> geometry;
  geometry.push_back(Triangle(RowVector3d(5, -2.5, 0), RowVector3d(-5.0, -2.5, 0), RowVector3d(0, 2.5, 0)));
  PointLight light = PointLight(RowVector3d(0, 15, -15), RowVector3d(36000, 36000, 36000));
  Camera cam = Camera(RowVector3d(0, 0, -15), RowVector3d(0, 0, 0), RowVector3d(0, 1, 0));
  Scene s = Scene(geometry, light, cam, 60, width, height);
  return s;  
} 

void printHit(MatrixXd img, int width, int height) {
	    for (int y= 0; y < height; y++) {	
			for (int x= 0; x < width; x++) {
            std::cout << img(y * width + x, 0);
        }
		std::cout << std::endl;
    }
}