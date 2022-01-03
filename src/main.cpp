#include <iostream>
#include <unistd.h>
#include <vector>
#include "rendering_engine.h"
#include <SDL2/SDL.h>

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture);

int main(int argc, char* argv[])
{
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event event;
        SDL_Rect r;

        int errorCode = initializeWindow(&window, &renderer, &texture);
        if (errorCode) {
                return errorCode;
        }
        r.w = 100;
        r.h = 100;

        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;

                r.x= (r.x + 1)% 1024;
                r.y=(r.y + 1)%768;

                SDL_SetRenderTarget(renderer, texture);
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(renderer);
                SDL_RenderDrawRect(renderer,&r);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
                SDL_RenderFillRect(renderer, &r);
                SDL_SetRenderTarget(renderer, NULL);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                
                // calculates to 60 fps
				SDL_Delay(1000 / 60);
        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}

int initializeWindow(SDL_Window ** window, SDL_Renderer ** renderer, SDL_Texture ** texture) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
                return 3;
        }

        *window = SDL_CreateWindow("SDL_test",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        1024, 768,
                        SDL_WINDOW_RESIZABLE);


        *renderer = SDL_CreateRenderer(*window, -1, 0);

        *texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
        return 0;
} 