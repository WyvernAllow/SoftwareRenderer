#include "renderer.h"
#include "bitmap_font.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct Renderer *renderer_create(uint16_t width, uint16_t height)
{
    struct Renderer *renderer = malloc(sizeof(struct Renderer));
    renderer->width = width;
    renderer->height = height;
    renderer->color_buffer = malloc(sizeof(uint8_t) * 4 * width * height);

    return renderer;
}

void renderer_destroy(struct Renderer *renderer)
{
    free(renderer->color_buffer);
    free(renderer);
}

void renderer_draw_pixel(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a)
{
    uint32_t index = (x + y * renderer->width) * 4;

    renderer->color_buffer[index + 0] = (uint8_t)(b * 255.0f);
    renderer->color_buffer[index + 1] = (uint8_t)(g * 255.0f);
    renderer->color_buffer[index + 2] = (uint8_t)(r * 255.0f);
    renderer->color_buffer[index + 3] = (uint8_t)(a * 255.0f);
}

void renderer_clear(struct Renderer *renderer, float r, float g, float b, float a)
{
    for(uint32_t i = 0; i < renderer->width * renderer->height; i++)
    {
        renderer->color_buffer[i * 4 + 0] = (uint8_t)(b * 255.0f);
        renderer->color_buffer[i * 4 + 1] = (uint8_t)(g * 255.0f);
        renderer->color_buffer[i * 4 + 2] = (uint8_t)(r * 255.0f);
        renderer->color_buffer[i * 4 + 3] = (uint8_t)(a * 255.0f);
    }
}

void renderer_draw_line(struct Renderer *renderer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, float r, float g, float b, float a)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int x = x0;
    int y = y0;

    int p = 2 * dy - dx;

    while(x < x1)
    {
        if(p >= 0)
        {
            renderer_draw_pixel(renderer, x, y, r, g, b, a);
            y++;
            p += 2 * dy - 2 * dx;
        }
        else
        {
            renderer_draw_pixel(renderer, x, y, r, g, b, a);

            p += 2 * dy;
        }

        x++;
    }
}

void renderer_draw_rect(struct Renderer *renderer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, float r, float g, float b, float a)
{
    for(uint16_t j = y; j < y + h; j++)
    {
        for(uint16_t i = x; i < x + w; i++)
        {
            renderer_draw_pixel(renderer, i, j, r, g, b, a);
        }
    }
}

void renderer_draw_char(struct Renderer *renderer, uint16_t x, uint16_t y, char character, float r, float g, float b, float a)
{
    int index = character - 32;
    
    for (int row = 0; row < 13; row++) 
    {
        for (int col = 0; col < 8; col++) 
        {
            unsigned char pixel = (bitmap_font[index][row] >> (7 - col)) & 1;
            
            int pixelX = x + col;
            int pixelY = y + row;
            
            if (pixel == 1) 
            {
                renderer_draw_pixel(renderer, pixelX, pixelY, r, g, b, a);
            }
        }
    }
}

void renderer_draw_string(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a, const char* string)
{
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        renderer_draw_char(renderer, x + i * 10, y, string[i], r, g, b, a);
    }
}

void renderer_draw_stringf(struct Renderer *renderer, uint16_t x, uint16_t y, float r, float g, float b, float a, const char* format, ...)
{
    char buffer[256];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    renderer_draw_string(renderer, x, y, r, g, b, a, buffer);
}