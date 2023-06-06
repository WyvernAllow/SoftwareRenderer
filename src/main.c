#include "graphics.h"

#include <SDL2/SDL_cpuinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 450

int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "Error: Could not initialize SDL. %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(!window)
    {
        fprintf(stderr, "Error: Could not create window. %s\n", SDL_GetError());
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    struct gfx_context *ctx = gfx_create(window_surface);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        ctx->surface = SDL_GetWindowSurface(window);
                    }
                    break;
            }
        }

        gfx_clear(ctx, 0.0, 0.0, 0.0);

        gfx_draw_stringf(ctx, 0, 0, 1.0, 1.0, 1.0, "Resolution: %ix%i", ctx->surface->w, ctx->surface->h);

        SDL_UpdateWindowSurface(window);
    }
}