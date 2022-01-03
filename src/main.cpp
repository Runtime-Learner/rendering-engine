#include <iostream>
#include <unistd.h>
#include <vector>
#include "rendering_engine.h"
#include <SDL2/SDL.h>

using Eigen::RowVector3d;
using Eigen::MatrixXd;

Scene getTriangleScene(int width, int height);
void printHit(MatrixXd img, int width, int height, std::vector< unsigned char > pixels, SDL_Renderer * renderer, SDL_Texture * texture);

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture, int width, int height);

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
        Scene s = getTriangleScene(width, height);
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
  std::vector<Triangle> geometry;
  geometry.push_back(Triangle(RowVector3d(5, -2.5, 0), RowVector3d(-5.0, -2.5, 0), RowVector3d(0, 2.5, 0)));
  PointLight light = PointLight(RowVector3d(0, 15, -15), RowVector3d(36000, 36000, 36000));
  Camera cam = Camera(RowVector3d(0, 0, -15), RowVector3d(0, 0, 0), RowVector3d(0, 1, 0));
  Scene s = Scene(geometry, light, cam, 60, width, height);
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
                        pixels[pxid + 1] = (int) (img(y * width + x, 0) * 255);
                        pixels[pxid + 2] = (int) (img(y * width + x, 1) * 255);
                        pixels[pxid + 3] = (int) (img(y * width + x, 2) * 255);
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