#include <iostream>
#include <unistd.h>
#include <memory>
#include <vector>
#include "rendering_engine.h"
#include "../lib/SDL2-2.0.20/include/SDL.h"

using Eigen::RowVector3d;
using Eigen::MatrixXd;

Scene getTriangleScene(int width, int height);
Scene getCornellBox(int width, int height);
Scene getBunnyScene(int width, int height, int scalingFactor);

void printHit(MatrixXd img, int width, int height, std::vector< unsigned char > pixels, SDL_Renderer * renderer, SDL_Texture * texture);

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture, int width, int height);

int main(int argc, char* argv[])
{
        int width, height, spp;

  	// validate user parameters
	if (argc != 4 || argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
		std::cout << "Invalid parameters: ./app <width> <height> <sample per pixel>\n";
		std::cout << "Defaulting to 100 x 100 image, 1 sample\n";
		width = 100;
		height = 100;
                spp = 1;
	}
	else {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
                spp = atoi(argv[3]);
	}


	if (width <= 0 || height <= 0 || spp <= 0) {
		std::cout << "Width, height, and spp must be an integer larger than 0.\n";
		return 0;
	}

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event event;
        std::vector< unsigned char > pixels( width * height * 4, 0 );

        int errorCode = initializeWindow(&window, &renderer, &texture, width, height);
        if (errorCode) {
                return errorCode;
        }

        Backward_Raytracing RT_renderer;
        //Scene s = getCornellBox(width, height);
        Scene s = getBunnyScene(width, height, 1000);
        std::cout << s.geometry.size() << std::endl;
        MatrixXd c = RT_renderer.render(s, spp); 
        printHit(c, s.resx, s.resy, pixels, renderer, texture);

        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;

                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);

                // calculates to 60 fps
                SDL_Delay(1000 / 60);
        }

        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
                return 3;
        }

        *window = SDL_CreateWindow("SDL_test",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        500, 500,
                        SDL_WINDOW_RESIZABLE);


        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

        *texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        return 0;
} 

Scene getTriangleScene(int width, int height) {
  std::vector<Shape> geometry = {
        new Triangle({5, -2.5, 0}, {-5.0, -2.5, 0}, {0, 2.5, 0}, new DiffuseBRDF({1, 0, 0}))
  };

  std::vector<Light> lights = {
        new PointLight({0, 15, -15}, {36000, 36000, 36000})
  };
  Camera cam = Camera({0, 0, -15}, {0, 0, 0}, {0, 1, 0});
  Scene s = Scene(geometry, lights, cam, 60, width, height);
  return s;  
} 

Scene getCornellBox(int width, int height) {
        std::vector<Shape> geometry = {
                // Floor
                new Triangle({552.8, 0, 0}, {0, 0, 0}, {0, 0, 559.2}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                new Triangle({552.8, 0, 0}, {0, 0, 559.2}, {552.8, 0, 559.2}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                // Ceiling
                new Triangle({556.0, 548.8, 0.0}, {556.0, 548.8, 559.2},{0.0, 548.8, 559.2}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                new Triangle({556.0, 548.8, 0.0}, {0.0, 548.8, 559.2}, {0.0, 548.8, 0.0}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                // Back Wall
                new Triangle({549.6, 0.0, 559.2}, {0.0, 0.0, 559.2}, {0.0, 548.8, 559.2}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                new Triangle({549.6, 0.0, 559.2}, {0.0, 548.8, 559.2}, {556.0, 548.8, 559.2}, new DiffuseBRDF({0.885809, 0.698859, 0.666422})),
                // Right Wall
                new Triangle({0.0, 0.0, 559.2 }, {0.0, 0.0, 0.0}, {0.0, 548.8,   0.0}, new DiffuseBRDF({0.1, 0.37798, 0.07})),
                new Triangle({0.0, 0.0, 559.2}, {0.0, 548.8, 0.0}, {0.0, 548.8, 559.2}, new DiffuseBRDF({0.1, 0.37798, 0.07})),
                // Left Wall
                new Triangle({552.8, 0.0, 0.0}, {549.6, 0.0, 559.2}, {556.0, 548.8, 559.2}, new DiffuseBRDF({0.57, 0.04, 0.04})),
                new Triangle({552.8, 0.0, 0.0}, {556.0, 548.8, 559.2}, {556.0, 548.8, 0.0}, new DiffuseBRDF({0.57, 0.04, 0.04})),
                // Short Block
                new Triangle({130.0, 165.0,  65.0}, {82.0, 165.0, 225.0}, {240.0, 165.0, 272.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({130.0, 165.0,  65.0}, {240.0 ,165.0, 272.0}, {290.0, 165.0, 114.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({290.0, 0.0, 114.0}, {290.0, 165.0, 114.0}, {240.0, 165.0, 272.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({290.0, 0.0, 114.0}, {240.0, 165.0, 272.0}, {240.0, 0.0, 272.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({130.0, 0.0, 65.0}, {130.0, 165.0, 65.0}, {290.0, 165.0, 114.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({130.0, 0.0, 65.0}, {290.0, 165.0, 114.0}, {290.0, 0.0, 114.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({82.0, 0.0, 225.0}, {82.0, 165.0, 225.0}, {130.0, 165.0, 65.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({82.0, 0.0, 225.0}, {130.0, 165.0, 65.0}, {130.0, 0.0, 65.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({240.0, 0.0, 272.0}, {240.0, 165.0, 272.0}, {82.0, 165.0, 225.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({240.0, 0.0, 272.0}, {82.0, 165.0, 225.0}, {82.0, 0.0, 225.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                // Tall Block
                new Triangle({423.0, 330.0, 247.0}, {265.0, 330.0, 296.0}, {314.0, 330.0, 456.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({423.0, 330.0, 247.0}, {314.0, 330.0, 456.0}, {472.0, 330.0, 406.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({423.0, 0.0, 247.0}, {423.0, 330.0, 247.0}, {472.0, 330.0, 406.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({423.0, 0.0, 247.0}, {472.0, 330.0,  406.0}, {472.0, 0.0, 406.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({472.0, 0.0, 406.0}, {472.0, 330.0,406.0}, {314.0, 330.0, 456.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({472.0, 0.0, 406.0}, {314.0, 330.0, 456.0}, {314.0, 0.0, 456.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({314.0, 0.0, 456.0}, {314.0, 330.0, 456.0}, {265.0, 330.0, 296.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({314.0, 0.0, 456.0}, {265.0,  330.0, 296.0}, {265.0, 0.0, 296.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({265.0, 0.0, 296.0}, {265.0, 330.0, 296.0}, {423.0, 330.0, 247.0}, new DiffuseBRDF({0.85, 0.85, 0.85})),
                new Triangle({265.0, 0.0, 296.0}, {423.0, 330.0, 247.0}, {423.0, 0.0, 247.0}, new DiffuseBRDF({0.85, 0.85, 0.85}))
        };
        std::vector<Light> lights = {
                new PointLight({178, 508, 279.5}, {0, 5e6, 5e6}),
                new PointLight({278, 508, 279.5}, {5e6, 5e6, 0}),
                new PointLight({378, 508, 279.5}, {5e6, 0, 5e6})
        };
        Camera cam = Camera({278, 273 , -800}, {278, 273, 0}, {0, 1, 0});
        Scene s = Scene(geometry, lights, cam, 38, width, height);
        return s;  
} 

Scene getBunnyScene(int width, int height, int scalingFactor) {
        double x_cam = (-0.09438042 + -0.0550398) / 2.0  * scalingFactor /2.0;
        double y_cam = (0.0333099 + 0.0573097) / 2.0  * scalingFactor * 2.0;
        std::vector<Shape> geometry = Scene::loadObjFile("../object_files/bunny.obj", 1000);
        std::vector<Light> lights;
        Camera camera = Camera({x_cam, y_cam, scalingFactor / 4.0}, {x_cam, y_cam, -1}, {0, 1, 0});
        Scene s = Scene(geometry, lights, camera, 60, width, height);
        return s;
}

void printHit(MatrixXd img, int width, int height, std::vector< unsigned char > pixels, SDL_Renderer * renderer, SDL_Texture * texture) {
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (int y= 0; y < height; y++) {	
		for (int x= 0; x < width; x++) {
                        int pxid =  (y * width + x) * 4;  
                        pixels[pxid] = 255; 
                        pixels[pxid + 1] = (int) (img(y * width + x, 2) * 255);
                        pixels[pxid + 2] = (int) (img(y * width + x, 1) * 255);
                        pixels[pxid + 3] = (int) (img(y * width + x, 0) * 255);
                }
        }
        SDL_UpdateTexture
        (
        texture,
        NULL,
        pixels.data(),
        width * 4
        );
}