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

void gfx_draw_line(struct gfx_context *context, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, float r, float g, float b)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int x = x1;
    int y = y1;

    int p = 2 * dy - dx;

    while(x < x1)
    {
        if(p >= 0)
        {
            gfx_draw_pixel(context, x, y, r, g, b);

            y++;
            p += 2 * dy - 2 * dx;
        }
        else
        {
            gfx_draw_pixel(context, x, y, r, g, b);

            p += 2 * dy;
        }

        x++;
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