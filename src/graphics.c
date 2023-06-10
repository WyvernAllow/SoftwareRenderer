#include "graphics.h"
#include "bitmap_font.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct gfx_context *gfx_create(SDL_Surface* surface)
{
    struct gfx_context *context = malloc(sizeof(struct gfx_context));
    context->surface = surface;

    return context;
}

void gfx_destroy(struct gfx_context *context)
{
    free(context);
}

void gfx_clear(struct gfx_context *context, float r, float g, float b)
{
    SDL_FillRect(context->surface, NULL, SDL_MapRGB(context->surface->format, (uint8_t)(r * 255.0f), (uint8_t)(g * 255.0f), (uint8_t)(b * 255.0f)));
}

void gfx_draw_pixel(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b)
{
    Uint32 *const target_pixel = (Uint32 *)((Uint8 *)context->surface->pixels + y * context->surface->pitch + x * context->surface->format->BytesPerPixel);
    *target_pixel = SDL_MapRGB(context->surface->format, (uint8_t)(r * 255.0f), (uint8_t)(g * 255.0f), (uint8_t)(b * 255.0f));
}

void gfx_draw_line(struct gfx_context *context, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, float r, float g, float b)
{
    // Calculate the differences and absolute differences between the coordinates
    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t sy = y0 < y1 ? 1 : -1;
    
    // Set initial error term and coordinates
    int16_t err = (dx > dy ? dx : -dy) / 2;
    int16_t current_x = x0;
    int16_t current_y = y0;

    // Loop until we reach the end point
    while (current_x != x1 || current_y != y1)
    {
        // Set the pixel at the current coordinates
        gfx_draw_pixel(context, current_x, current_y, r, g, b);

        // Calculate the next coordinates
        int16_t err2 = err;
        if (err2 > -dx)
        {
            err -= dy;
            current_x += sx;
        }
        if (err2 < dy)
        {
            err += dx;
            current_y += sy;
        }
    }
}

void gfx_draw_rect(struct gfx_context *context, uint16_t x, uint16_t y, uint16_t w, uint16_t h, float r, float g, float b)
{
    for(uint16_t j = y; j < y + h; j++)
    {
        for(uint16_t i = x; i < x + w; i++)
        {
            gfx_draw_pixel(context, i, j, r, g, b);
        }
    }
}

void gfx_draw_char(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, char character)
{
    int index = character - 32;
    
    for (int row = 0; row < 13; row++) 
    {
        for (int col = 0; col < 8; col++) 
        {
            unsigned char pixel = (bitmap_font[index][row] >> (7 - col)) & 1;
            
            int pixelX = x + col;
            int pixelY = y + (12 - row);
            
            if (pixel == 1) 
            {
                gfx_draw_pixel(context, pixelX, pixelY, r, g, b);
            }
        }
    }
}

void gfx_draw_string(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, const char* string)
{
    int length = strlen(string);

    for (int i = 0; i < length; i++)
    {
        gfx_draw_char(context, x + i * 10, y, r, g, b, string[i]);
    }
}

void gfx_draw_stringf(struct gfx_context *context, uint16_t x, uint16_t y, float r, float g, float b, const char* format, ...)
{
    char buffer[256];
    
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    gfx_draw_string(context, x, y, r, g, b, buffer);
}