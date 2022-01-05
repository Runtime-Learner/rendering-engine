#include <iostream>
#include <unistd.h>
#include <vector>
#include "rendering_engine.h"
#include <SDL2/SDL.h>

using Eigen::RowVector3d;
using Eigen::MatrixXd;

Scene getTriangleScene(int width, int height);
Scene getCornellBox(int width, int height);
void printHit(MatrixXd img, int width, int height, std::vector< unsigned char > pixels, SDL_Renderer * renderer, SDL_Texture * texture);

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture, int width, int height);

int main(int argc, char* argv[])
{
        int width, height;

  	// validate user parameters
	if (argc != 3 || argv[1] == NULL || argv[2] == NULL) {
		std::cout << "Invalid parameters: ./app <width> <height>\n";
		std::cout << "Defaulting to 100 x 100 image\n";
		width = 100;
		height = 100;
	}
	else {
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}


	if (width <= 0 || height <= 0) {
		std::cout << "invalid width or height parameter. Must be an integer larger than 0.\n";
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
        Scene s = getCornellBox(width, height);
        std::cout << s.geometry.size() << std::endl;
        MatrixXd c = RT_renderer.render(s); 
        printHit(c, s.resx, s.resy, pixels, renderer, texture);

        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;
                
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
                        width, height,
                        SDL_WINDOW_RESIZABLE);


        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

        *texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        return 0;
} 

Scene getTriangleScene(int width, int height) {
  std::vector<Triangle> geometry = {
        Triangle({5, -2.5, 0}, {-5.0, -2.5, 0}, {0, 2.5, 0}, {1, 0, 0})
  };
  PointLight light = PointLight({0, 15, -15}, {36000, 36000, 36000});
  Camera cam = Camera({0, 0, -15}, {0, 0, 0}, {0, 1, 0});
  Scene s = Scene(geometry, light, cam, 60, width, height);
  return s;  
} 

Scene getCornellBox(int width, int height) {
  std::vector<Triangle> geometry = {
    // Floor
    Triangle({552.8, 0, 0}, {0, 0, 0}, {0, 0, 559.2}, {0.885809, 0.698859, 0.666422}),
    Triangle({552.8, 0, 0}, {0, 0, 559.2}, {552.8, 0, 559.2}, {0.885809, 0.698859, 0.666422}),
    // Ceiling
    Triangle({556.0, 548.8, 0.0}, {556.0, 548.8, 559.2},{0.0, 548.8, 559.2}, {0.885809, 0.698859, 0.666422}),
    Triangle({556.0, 548.8, 0.0}, {0.0, 548.8, 559.2}, {0.0, 548.8, 0.0}, {0.885809, 0.698859, 0.666422}),
    // Back Wall
    Triangle({549.6, 0.0, 559.2}, {0.0, 0.0, 559.2}, {0.0, 548.8, 559.2}, {0.885809, 0.698859, 0.666422}),
    Triangle({549.6, 0.0, 559.2}, {0.0, 548.8, 559.2}, {556.0, 548.8, 559.2}, {0.885809, 0.698859, 0.666422}),
    // Right Wall
    Triangle({0.0, 0.0, 559.2 }, {0.0, 0.0, 0.0}, {0.0, 548.8,   0.0}, {0.1, 0.37798, 0.07}),
    Triangle({0.0, 0.0, 559.2}, {0.0, 548.8, 0.0}, {0.0, 548.8, 559.2}, {0.1, 0.37798, 0.07}),
    // Left Wall
    Triangle({552.8, 0.0, 0.0}, {549.6, 0.0, 559.2}, {556.0, 548.8, 559.2}, {0.57, 0.04, 0.04}),
    Triangle({552.8, 0.0, 0.0}, {556.0, 548.8, 559.2}, {556.0, 548.8, 0.0}, {0.57, 0.04, 0.04}),
    // Short Block
    Triangle({130.0, 165.0,  65.0}, {82.0, 165.0, 225.0}, {240.0, 165.0, 272.0},  {0.85, 0.85, 0.85}),
    Triangle({130.0, 165.0,  65.0}, {240.0 ,165.0, 272.0}, {290.0, 165.0, 114.0}, {0.85, 0.85, 0.85}),
    Triangle({290.0, 0.0, 114.0}, {290.0, 165.0, 114.0}, {240.0, 165.0, 272.0}, {0.85, 0.85, 0.85}),
    Triangle({290.0, 0.0, 114.0}, {240.0, 165.0, 272.0}, {240.0, 0.0, 272.0}, {0.85, 0.85, 0.85}),
    Triangle({130.0, 0.0, 65.0}, {130.0, 165.0, 65.0}, {290.0, 165.0, 114.0}, {0.85, 0.85, 0.85}),
    Triangle({130.0, 0.0, 65.0}, {290.0, 165.0, 114.0}, {290.0, 0.0, 114.0}, {0.85, 0.85, 0.85}),
    Triangle({82.0, 0.0, 225.0}, {82.0, 165.0, 225.0}, {130.0, 165.0, 65.0}, {0.85, 0.85, 0.85}),
    Triangle({82.0, 0.0, 225.0}, {130.0, 165.0, 65.0}, {130.0, 0.0, 65.0}, {0.85, 0.85, 0.85}),
    Triangle({240.0, 0.0, 272.0}, {240.0, 165.0, 272.0}, {82.0, 165.0, 225.0}, {0.85, 0.85, 0.85}),
    Triangle({240.0, 0.0, 272.0}, {82.0, 165.0, 225.0}, {82.0, 0.0, 225.0}, {0.85, 0.85, 0.85}),
    // Tall Block
    Triangle({423.0, 330.0, 247.0}, {265.0, 330.0, 296.0}, {314.0, 330.0, 456.0}, {0.85, 0.85, 0.85}),
    Triangle({423.0, 330.0, 247.0}, {314.0, 330.0, 456.0}, {472.0, 330.0, 406.0}, {0.85, 0.85, 0.85}),
    Triangle({423.0, 0.0, 247.0}, {423.0, 330.0, 247.0}, {472.0, 330.0, 406.0}, {0.85, 0.85, 0.85}),
    Triangle({423.0, 0.0, 247.0}, {472.0, 330.0,  406.0}, {472.0, 0.0, 406.0}, {0.85, 0.85, 0.85}),
    Triangle({472.0, 0.0, 406.0}, {472.0, 330.0,406.0}, {314.0, 330.0, 456.0}, {0.85, 0.85, 0.85}),
    Triangle({472.0, 0.0, 406.0}, {314.0, 330.0, 456.0}, {314.0, 0.0, 456.0}, {0.85, 0.85, 0.85}),
    Triangle({314.0, 0.0, 456.0}, {314.0, 330.0, 456.0}, {265.0, 330.0, 296.0}, {0.85, 0.85, 0.85}),
    Triangle({314.0, 0.0, 456.0}, {265.0,  330.0, 296.0}, {265.0, 0.0, 296.0}, {0.85, 0.85, 0.85}),
    Triangle({265.0, 0.0, 296.0}, {265.0, 330.0, 296.0}, {423.0, 330.0, 247.0}, {0.85, 0.85, 0.85}),
    Triangle({265.0, 0.0, 296.0}, {423.0, 330.0, 247.0}, {423.0, 0.0, 247.0}, {0.85, 0.85, 0.85})
  };
  PointLight light = PointLight({278, 508, 279.5}, {5e6, 5e6, 5e6});
  Camera cam = Camera({278, 273 , -800}, {278, 273, 0}, {0, 1, 0});
  Scene s = Scene(geometry, light, cam, 38, width, height);
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
        SDL_RenderCopy(renderer, texture, NULL, NULL);
}
